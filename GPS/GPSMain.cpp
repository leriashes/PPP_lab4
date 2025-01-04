#include <iostream>
#include "..\GPS.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel Nav("NAV", "127.0.0.1", 8484, false);
    GPS gps(&Nav);

    cout << "Модуль GPS\n\n";
    gps.start();
}
