#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

template <typename T>
class ThreadWrap
{
private:
    T* module;
    HANDLE threadHandle;

    static DWORD WINAPI threadFunction(LPVOID lpParam) {
        T* module = static_cast<T*>(lpParam);
        module->start();  // ������ ��������� ������ ������
        return 0;
    }

public:
    // ����������� �������� ��������� �� ������
    ThreadWrap(T* module) : module(module), threadHandle(NULL) {}

    // ����� ��� ������ ������
    void startThread() {
        threadHandle = CreateThread(NULL, 0, threadFunction, module, 0, NULL);
        if (threadHandle == NULL) {
            cerr << "������ ��� �������� ������.\n";
        }
    }

    // �������� ���������� ������
    void waitForThread() {
        if (threadHandle != NULL) {
            WaitForSingleObject(threadHandle, INFINITE);
            CloseHandle(threadHandle);
        }
    }
};
