#pragma once
#include <windows.h>
#include <iostream>
#include "MoonwalkerModule.h"
using namespace std;

class ThreadWrap
{
private:
    MoonwalkerModule* module;
    HANDLE threadHandle;

    static DWORD WINAPI threadFunction(LPVOID lpParam);

public:
    // ����������� �������� ��������� �� ������
    ThreadWrap(MoonwalkerModule* module) : module(module), threadHandle(NULL) {}

    void startThread(); // ����� ��� ������ ������
    void waitForThread(); // �������� ���������� ������
};
