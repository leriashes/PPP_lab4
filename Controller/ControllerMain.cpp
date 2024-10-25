#include <iostream>
#include "..\Controller.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Img("IMG", 1024);

    TReliableChannel NewPath("NewPath", 1024), Path("Path", 1024), Finish("Finish", 1024);
    TReliableChannel Start("Start", 1024), Stop("Stop", 1024);
    TReliableChannel Take("Take", 1024), Ready("Ready", 1024);

    Controller controller(&Path, &NewPath, &Img, &Start, &Stop, &Take, &Ready, &Finish);

    cout << "Модуль КОНТРОЛЛЕР\n\n";
    controller.start();
}
