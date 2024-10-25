#pragma once
#include "TSemaphore.h"
#include "TData.h"

class TChannel
{
protected:
    TSemaphore* empty;
    TData data;

public:
    void put(TData t);
    void get(TData* resultData);
    TChannel();
    ~TChannel();
};