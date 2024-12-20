#include "TEstafeta.h"

void TEstafeta::estafeta()
{
	if (((numW > 0) || (numR > 0)) && (waitW > 0)) {
		empty->V();
	}
	else if ((numR == 0) && (numW == 0) && (waitW > 0)) {
		waitW--;
		w->V();
	}
	else if ((numW == 0) && (waitW == 0) && (waitR > 0)) {
		waitR--;
		r->V();
	}
	else {
		empty->V();
	}

	cout << " !!! Передача эстафеты !!!";
}

void TEstafeta::put(TData t, int num)
{
	cout << "   >>> Писатель " << num << " ожидает эстафету (в очереди уже: " << waitW << " П, "  << waitR << " Ч, работают: " << numW << " П, " << numR << " Ч)";
	empty->P();

	if (numR > 0 || numW > 0) {
		waitW++;
		empty->V();
		w->P();
	}

	cout << "\n    *** писатель " << num << ": ПОЛУЧАЮ эстафету *** (в очереди: " << waitW << " П, " << waitR << " Ч, работают: " << numW << " П, " << numR << " Ч)";

	numW++;
	estafeta();

	int size = sizeof(t);

	if (buffer == nullptr || size > bufferSize)
		cerr << "Ошибка: не удалось записать в отображаемый файл." << endl;

	memcpy(buffer, &t, size);

	this_thread::sleep_for(chrono::milliseconds(3000));


	cout << "\n    *** писатель " << num << ": ПЕРЕДАЮ эстафету *** (в очереди: " << waitW << " П, " << waitR << " Ч, работают: " << numW - 1 << " П, " << numR << " Ч)";

	empty->P();
	numW--;
	estafeta();
}

void TEstafeta::get(TData* resultData, int num)
{
	cout << "   <<< Читатель " << num << " ожидает эстафету (в очереди уже: " << waitW << " П, " << waitR << " Ч, работают: " << numW << " П, " << numR << " Ч)";
	empty->P();

	if (numW > 0) {
		waitR++;
		empty->V();
		r->P();
	}

	cout << "\n    *** чиатель " << num << ": ПОЛУЧАЮ эстафету *** (в очереди: " << waitW << " П, " << waitR << " Ч, работают: " << numW << " П, " << numR << " Ч)";

	numR++;
	estafeta();

	int size = sizeof(*resultData);

	if (buffer == nullptr || size > bufferSize)
		cerr << "Ошибка: не удалось считать из отображаемого файла." << endl;

	memcpy(resultData, buffer, size);

	this_thread::sleep_for(chrono::milliseconds(2000));


	cout << "\n    *** читатель " << num << ": ПЕРЕДАЮ эстафету *** (в очереди: " << waitW << " П, " << waitR << " Ч, работают: " << numW << " П, " << numR - 1 << " Ч)";

	empty->P();
	numR--;
	estafeta();
}

TEstafeta::TEstafeta(const char* name, size_t size): TChannel(name, size)
{
	r = new TSemaphore((string(name) + "_semRRR").c_str(), 0);
	w = new TSemaphore((string(name) + "_semWWW").c_str(), 0);

	delete empty;
	empty = new TSemaphore((string(name) + "_semEEE").c_str(), 1);

	numR = numW = waitR = waitW = 0;
}

TEstafeta::~TEstafeta()
{
	if (buffer)
		UnmapViewOfFile(buffer);

	if (fileMem)
		CloseHandle(fileMem);

	delete empty;
	delete r;
	delete w;
}
