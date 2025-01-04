#include <iostream>
#include "..\Mover.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel Start("Start", "127.0.0.1", 8484), Stop("Stop", "127.0.0.1", 8484);

    Mover mover(&Start, &Stop);

    cout << "Модуль ПЕРЕДВИЖЕНИЯ\n\n";
    mover.start();
}
