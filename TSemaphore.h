#pragma once
class TSemaphore
{
private:
    int count;  // ��������� �������

public:
    void P(); 
    void V();

    TSemaphore(int start);
    ~TSemaphore();
};