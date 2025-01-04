#include <iostream>
#include "..\Mover.h"
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");

    string addr;
    int port;

    if (argc < 3) {
        addr = "127.0.0.1";
        port = 8484;
    }
    else
    {
        addr = argv[1];
        port = stoi(argv[2]);
    }

    NetworkChannel Start("Start", addr, port), Stop("Stop", addr, port);

    Mover mover(&Start, &Stop);

    cout << "Модуль ПЕРЕДВИЖЕНИЯ\n\n";
    mover.start();
}
