#include "ThreadWrap.h"

DWORD WINAPI ThreadWrap::threadFunction(LPVOID lpParam)
{
    MoonwalkerModule* module = static_cast<MoonwalkerModule*>(lpParam);
    module->start();  // ������ ��������� ������ ������
    return 0;
}

void ThreadWrap::startThread()
{
    threadHandle = CreateThread(NULL, 0, threadFunction, module, 0, NULL);
    if (threadHandle == NULL) {
        cerr << "������ ��� �������� ������.\n";
    }
}

void ThreadWrap::waitForThread() {
    if (threadHandle != NULL) {
        WaitForSingleObject(threadHandle, INFINITE);
        CloseHandle(threadHandle);
    }
}