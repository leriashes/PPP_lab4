#include "TChannel.h"
TChannel::TChannel(const char* name, size_t size) : 
    channelName(name), bufferSize(size), buffer(nullptr), fileMem(NULL)
{
    empty = new TSemaphore((string(name) + "_semEmpty").c_str(), 0);

    // ������� ��� ��������� ����, ������������ �� ������
    fileMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (wstring(name, name + strlen(name))).c_str());
    if (fileMem == NULL) 
    {
        fileMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, static_cast<DWORD>(size), (wstring(name, name + strlen(name))).c_str());
    }

    // ���������� ���� �� ������
    if (fileMem != NULL) 
    {
        buffer = MapViewOfFile(fileMem, FILE_MAP_ALL_ACCESS, 0, 0, size);

        if (buffer == NULL) 
            cerr << "������: �� ������� ���������� ���� � ������." << endl;
    }
    else 
    {
        cerr << "������: �� ������� ������� ��� ������� ������������ ����." << endl;
    }
}

void TChannel::put(TData t)
{
    int size = sizeof(t);

    if (buffer == nullptr || size > bufferSize)
        cerr << "������: �� ������� �������� � ������������ ����." << endl;

    memcpy(buffer, &t, size);

    empty->V();
}

void TChannel::get(TData* resultData)
{
    int size = sizeof(*resultData);

    if (buffer == nullptr || size > bufferSize)
        cerr << "������: �� ������� ������� �� ������������� �����." << endl;

    empty->P();

    memcpy(resultData, buffer, size);
}

TChannel::~TChannel()
{
    if (buffer) 
        UnmapViewOfFile(buffer);

    if (fileMem)
        CloseHandle(fileMem);

    delete this->empty;
}
