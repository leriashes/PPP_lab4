#include "TChannel.h"

void TChannel::put(TData t)
{
    free->P();
    data = t;
    empty->V();
}

void TChannel::get(TData* resultData)
{
    empty->P();
    *resultData = this->data;
    free->V();
}

TChannel::TChannel()
{
    free = new TSemaphore(1);
    empty = new TSemaphore(0);
}

TChannel::~TChannel()
{
    delete this->free;
    delete this->empty;
}
