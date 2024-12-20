#pragma once
#include "TChannel.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

class TEstafeta :
    public TChannel
{
private:
    TSemaphore* r;
    TSemaphore* w;

    int waitR;
    int waitW;
    int numW;
    int numR;

    void estafeta();

public:
    void put(TData t, int num);
    void get(TData* resultData, int num);
    TEstafeta(const char* name, size_t size);
    ~TEstafeta();
};

