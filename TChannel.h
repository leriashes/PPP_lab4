#pragma once
#include "TSemaphore.h"
#include "TData.h"

class TChannel
{
private:
    TSemaphore* free;
    TSemaphore* empty;
    TData data;

public:
    void put(TData t);
    void get(TData* resultData);
    TChannel();
    ~TChannel();
};