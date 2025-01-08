#include "Controller.h"

Controller::Controller(int num, TSemaphore* print, TSemaphore* free, TChannel* service, TChannel* Take1, TChannel* Ready1, TChannel* Take2, TChannel* Ready2)
{
	this->num = num;
	this->print = print;
	this->free = free;

	this->service = service;
	this->Take1 = Take1;
	this->Ready1 = Ready1;
	this->Take2 = Take2;
	this->Ready2 = Ready2;
}

void Controller::start()
{
	print->P();
	cout << "\nКонтроллер запущен " << num << endl;
	print->V();

	int i = 0;

	while (i < 1) {

		print->P();
		cout << "   загрузка...  " << num << endl;
		print->V();

		Sleep(200);

		print->P();
		cout << "  Готов к работе, нужны манипуляторы (NEED_FORKS)   " << num << endl;
		print->V();

		service->put(TData(NEED_FORKS, 0));

		free->P();

		print->P();
		cout << "   Работает  " << num << endl;
		print->V();

		sendTake();
		getReady();

		print->P();
		cout << "\n";
		print->V();

		service->put(TData(FREE_FORKS, 0));

		print->P();
		cout << "   Работа завершена, освобождает манипуляторы (FREE_FORKS)  " << num << endl;
		print->V();

		i++;
	}

	print->P();
	cout << "\nКонтроллер остановлен   " << num << endl;
	print->V();

}

void Controller::sendTake()
{
	print->P();
	cout << "\n" << num << " КОНТРОЛЛЕР .1: отправка команды 'начать сбор грунта' в Манипулятор...";
	print->V();

	TData data(0, 4);
	Take1->put(data);
	Take2->put(data);
}

void Controller::getReady()
{
	print->P();
	cout << "\n" << num << " КОНТРОЛЛЕР .2_1: ожидание сообщения о завершении от Манипулятора...";
	print->V();

	TData data;
	Ready1->get(&data);
	Ready2->get(&data);

	print->P();
	cout << "\n" << num << " КОНТРОЛЛЕР .2_2: получено сообщение о завершении от Манипулятора";
	print->V();
}
