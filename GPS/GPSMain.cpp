#include <iostream>
#include "..\GPS.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Coords("Coords", 4096);
    GPS gps(&Coords);

    cout << "Модуль GPS\n\n";
    gps.start();
}
