#pragma once
#include "TSemaphore.h"
#include "TData.h"

class TChannel
{
protected:
    TSemaphore* empty;
    TData data;

public:
    virtual void put(TData t);
    virtual void get(TData* resultData);
    TChannel();
    virtual ~TChannel();
};