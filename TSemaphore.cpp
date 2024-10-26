#include "TSemaphore.h"

void TSemaphore::P()
{ 
    cout << "\n��� ������� " << endl;
	WaitForSingleObject(Sem, INFINITE);
    cout << "\n�������� ������� " << endl;
}

void TSemaphore::V()
{
    LONG previousCount = 0;
    BOOL result = ReleaseSemaphore(Sem, 1, &previousCount);
    if (result) {
        std::cout << "\n������� ��� 0 - Current semaphore count: " << previousCount << std::endl;
    }
    else {
        std::cerr << "\n������� ��� 1 - Failed to get semaphore count. Error: " << GetLastError() << std::endl;
    }

	//ReleaseSemaphore(Sem, 1, NULL);

    cout << "\n������� ������� " << endl;
}

TSemaphore::TSemaphore(const char* name, int start)
{
    //(wstring(name, name + strlen(name))).c_str()
    Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, (wstring(name, name + strlen(name))).c_str());

    if (Sem == NULL)
    {
        int s = (start > 0);
        Sem = CreateSemaphore(NULL, s, 1, (wstring(name, name + strlen(name))).c_str());


        if (Sem == NULL) {
            std::cerr << "Failed to create semaphore. Error: " << GetLastError() << std::endl;
            return;
        }

        cout << "\n������ ������� " << name << endl;
    }
    else
    {
        cout << "\n������ ������� " << name << endl;
    }
}

TSemaphore::~TSemaphore()
{
    if (Sem != NULL)
        CloseHandle(Sem);
}
