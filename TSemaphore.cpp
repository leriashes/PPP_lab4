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
    Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, (LPCWSTR)name);

    if (Sem == NULL)
    {
        int s = (start > 0);
        Sem = CreateSemaphore(NULL, s, 1, (LPCWSTR)name);
    }
}

TSemaphore::~TSemaphore()
{
    if (Sem)
        CloseHandle(Sem);
}
