#include "TReliableChannel.h"

void TReliableChannel::put(TData t)
{
    int size = sizeof(t);

    if (buffer == nullptr || size > bufferSize)
        cerr << "Ошибка: не удалось записать в отображаемый файл." << endl;

    free->P();

    memcpy(buffer, &t, size);

    empty->V();
}

void TReliableChannel::get(TData* resultData)
{
    int size = sizeof(*resultData);

    if (buffer == nullptr || size > bufferSize)
        cerr << "Ошибка: не удалось считать из отображаемого файла." << endl;

    empty->P();

    memcpy(resultData, buffer, size);
    
    free->V();
}

TReliableChannel::TReliableChannel(const char* name, size_t size) : TChannel(name, size)
{
    free = new TSemaphore((string(name) + "_semFree").c_str(), 1);
}

TReliableChannel::~TReliableChannel()
{
    /*delete this->free;
    delete this->empty;*/
}
