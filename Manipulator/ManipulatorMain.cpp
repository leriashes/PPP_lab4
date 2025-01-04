#include <iostream>
#include "..\Manipulator.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel Take("Take", "127.0.0.1", 8484), Ready("Ready", "127.0.0.1", 8484);

    Manipulator manipulator(&Take, &Ready);

    cout << "МАНИПУЛЯТОР\n\n";
    manipulator.start();
}
