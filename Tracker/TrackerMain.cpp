#include <iostream>
#include "..\Tracker.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TReliableChannel Nav("Nav", 1024), Location("Location", 1024);

    Tracker tracker(&Nav, &Location);

    cout << "Модуль ОТСЛЕЖИВАНИЯ\n\n";
    tracker.start();
}
