#include <iostream>
#include "..\Navigator.h"
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

    NetworkChannel Nav("NAV", addr, port, false);
    NetworkChannel NewPath("NewPath", addr, port), Path("Path", addr, port);

    Navigator navigator(&NewPath, &Nav, &Path);

    cout << "Модуль НАВИГАТОР\n\n";
    navigator.start();
}
