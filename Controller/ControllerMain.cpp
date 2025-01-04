#include <iostream>
#include "..\Controller.h"
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

    NetworkChannel Img("IMG", addr, port, false);

    NetworkChannel NewPath("NewPath", addr, port), Path("Path", addr, port), Finish("Finish", addr, port);
    NetworkChannel Start("Start", addr, port), Stop("Stop", addr, port);
    NetworkChannel Take("Take", addr, port), Ready("Ready", addr, port);

    Controller controller(&Path, &NewPath, &Img, &Start, &Stop, &Take, &Ready, &Finish);

    cout << "Модуль КОНТРОЛЛЕР\n\n";
    controller.start();
}
