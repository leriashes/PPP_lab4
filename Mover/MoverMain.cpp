#include <iostream>
#include "..\Mover.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TReliableChannel Start("Start", 1024), Stop("Stop", 1024);

    Mover mover(&Start, &Stop);

    cout << "Модуль ПЕРЕДВИЖЕНИЯ\n\n";
    mover.start();
}
