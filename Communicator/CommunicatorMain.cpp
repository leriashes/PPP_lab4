#include <iostream>
#include "..\Communicator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TReliableChannel NewPath("NewPath", 1024), Finish("Finish", 1024);

    Communicator communicator(&NewPath, &Finish);

    cout << "Модуль КОММУНИКАЦИИ\n\n";
    communicator.start();
}
