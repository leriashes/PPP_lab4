#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;

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