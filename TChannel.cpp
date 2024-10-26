#include "TChannel.h"
TChannel::TChannel(const char* name, size_t size) : 
    channelName(name), bufferSize(size), buffer(nullptr), fileMem(NULL)
{
    empty = new TSemaphore((string(name) + "_semEmpty").c_str(), 0);

    // Создаем или открываем файл, отображаемый на память
    fileMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (wstring(name, name + strlen(name))).c_str());
    if (fileMem == NULL) 
    {
        fileMem = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, static_cast<DWORD>(size), (wstring(name, name + strlen(name))).c_str());
    }

    // Отображаем файл на память
    if (fileMem != NULL) 
    {
        buffer = MapViewOfFile(fileMem, FILE_MAP_ALL_ACCESS, 0, 0, size);

        if (buffer == NULL) 
            cerr << "Ошибка: не удалось отобразить файл в память." << endl;
    }
    else 
    {
        cerr << "Ошибка: не удалось создать или открыть отображаемый файл." << endl;
    }
}

void TChannel::put(TData t)
{
    int size = sizeof(t);

    if (buffer == nullptr || size > bufferSize)
        cerr << "Ошибка: не удалось записать в отображаемый файл." << endl;

    memcpy(buffer, &t, size);

    empty->V();
}

void TChannel::get(TData* resultData)
{
    int size = sizeof(*resultData);

    if (buffer == nullptr || size > bufferSize)
        cerr << "Ошибка: не удалось считать из отображаемого файла." << endl;

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
