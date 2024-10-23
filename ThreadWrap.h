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
        module->start();  // Запуск основного метода модуля
        return 0;
    }

public:
    // Конструктор получает указатель на модуль
    ThreadWrap(T* module) : module(module), threadHandle(NULL) {}

    // Метод для старта потока
    void startThread() {
        threadHandle = CreateThread(NULL, 0, threadFunction, module, 0, NULL);
        if (threadHandle == NULL) {
            cerr << "Ошибка при создании потока.\n";
        }
    }

    // Ожидание завершения потока
    void waitForThread() {
        if (threadHandle != NULL) {
            WaitForSingleObject(threadHandle, INFINITE);
            CloseHandle(threadHandle);
        }
    }
};
