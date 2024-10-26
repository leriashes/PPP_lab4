#include "TSemaphore.h"

void TSemaphore::P()
{
	WaitForSingleObject(Sem, INFINITE);
}

void TSemaphore::V()
{
    ReleaseSemaphore(Sem, 1, NULL);
}

TSemaphore::TSemaphore(const char* name, int start)
{
    Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, (wstring(name, name + strlen(name))).c_str());

    if (Sem == NULL)
    {
        int s = (start > 0);
        Sem = CreateSemaphore(NULL, s, 1, (wstring(name, name + strlen(name))).c_str());
    }
}

TSemaphore::~TSemaphore()
{
    if (Sem != NULL)
        CloseHandle(Sem);
}
