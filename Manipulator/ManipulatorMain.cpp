#include <iostream>
#include "..\Manipulator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TReliableChannel Take("Take", 1024), Ready("Ready", 1024);

    Manipulator manipulator(&Take, &Ready);

    cout << "МАНИПУЛЯТОР\n\n";
    manipulator.start();
}
