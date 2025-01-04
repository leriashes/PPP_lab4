#include <iostream>
#include "..\Communicator.h"
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

    NetworkChannel NewPath("NewPath", addr, port), Finish("Finish", addr, port);

    Communicator communicator(&NewPath, &Finish);

    cout << "Модуль КОММУНИКАЦИИ\n\n";
    communicator.start();
}
