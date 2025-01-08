#pragma once
#include <Windows.h>
#include <iostream>
using namespace std;

enum {
    OK = 100,
    FROM_RIGHT,
    RET_RIGHT,
    NEED_FORKS,
    FREE_FORKS
};

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