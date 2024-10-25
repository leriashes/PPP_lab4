#pragma once
#include <Windows.h>

class TSemaphore
{
private:
    HANDLE Sem;

public:
    void P(); 
    void V();

    TSemaphore(const char* name, int start);
    ~TSemaphore();
};