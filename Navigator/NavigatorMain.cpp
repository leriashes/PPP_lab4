#include <iostream>
#include "..\Navigator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel Nav("NAV", "127.0.0.1", 8484, false);
    NetworkChannel NewPath("NewPath", "127.0.0.1", 8484), Path("Path", "127.0.0.1", 8484);

    Navigator navigator(&NewPath, &Nav, &Path);

    cout << "Модуль НАВИГАТОР\n\n";
    navigator.start();
}
