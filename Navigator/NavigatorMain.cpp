#include <iostream>
#include "..\Navigator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Nav("NAV", 1024);
    TReliableChannel NewPath("NewPath", 1024), Path("Path", 1024);

    Navigator navigator(&NewPath, &Nav, &Path);

    cout << "Модуль НАВИГАТОР\n\n";
    navigator.start();
}
