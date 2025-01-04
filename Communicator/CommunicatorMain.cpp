#include <iostream>
#include "..\Communicator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel NewPath("NewPath", "127.0.0.1", 8484), Finish("Finish", "127.0.0.1", 8484);

    Communicator communicator(&NewPath, &Finish);

    cout << "Модуль КОММУНИКАЦИИ\n\n";
    communicator.start();
}
