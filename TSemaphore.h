#pragma once
class TSemaphore
{
private:
    int count;  // локальный счетчик

public:
    void P(); 
    void V();

    TSemaphore(int start);
    ~TSemaphore();
};