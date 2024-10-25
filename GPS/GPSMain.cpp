#include <iostream>
#include "..\GPS.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Nav("NAV", 4096);
    GPS gps(&Nav);

    cout << "Модуль GPS\n\n";
    gps.start();
}
