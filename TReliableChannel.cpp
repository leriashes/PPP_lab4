#include "TReliableChannel.h"

void TReliableChannel::put(TData t)
{
    free->P();
    data = t;
    empty->V();
}

void TReliableChannel::get(TData* resultData)
{
    empty->P();
    *resultData = this->data;
    free->V();
}

TReliableChannel::TReliableChannel()
{
    free = new TSemaphore(1);
    empty = new TSemaphore(0);
}

TReliableChannel::~TReliableChannel()
{
    delete this->free;
    delete this->empty;
}

