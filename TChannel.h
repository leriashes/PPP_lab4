#pragma once
#include "TSemaphore.h"
#include "TData.h"

class TChannel
{
protected:
    TSemaphore* empty;
    HANDLE fileMem;
    void* buffer;
    const char* channelName;
    const size_t bufferSize;

public:
    virtual void put(TData t);
    virtual void get(TData* resultData);
    TChannel(const char* name, size_t size);
    virtual ~TChannel();
};