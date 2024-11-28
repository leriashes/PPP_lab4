#include <iostream>
#include "..\Navigator.h"
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");

    int num = 0;

    if (argc == 2)
    {
        num = (int)argv[1][0] - 48;
    }

    TChannel Coords("Coords", 1024);
    TReliableChannel Nav("Nav", 1024), Path("Path", 1024), Location("Location", 1024);

    Navigator navigator(&Nav, &Coords, &Path, &Location);

    if (num != 0)
    {
        cout << "Модуль НАВИГАТОР " << num << "\n\n";
    }
    else
    {
        cout << "Модуль НАВИГАТОР\n\n";
    }

    navigator.start();
}
