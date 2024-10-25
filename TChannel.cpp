#include "TChannel.h"

void TChannel::put(TData t)
{
    data = t;
    empty->V();
}

void TChannel::get(TData* resultData)
{
    empty->P();
    *resultData = this->data;
}

TChannel::TChannel()
{
    empty = new TSemaphore(0);
}

TChannel::~TChannel()
{
    delete this->empty;
}
