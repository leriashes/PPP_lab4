#include <iostream>
#include "..\Controller.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel Img("IMG", "127.0.0.1", 8484, false);

    NetworkChannel NewPath("NewPath", "127.0.0.1", 8484), Path("Path", "127.0.0.1", 8484), Finish("Finish", "127.0.0.1", 8484);
    NetworkChannel Start("Start", "127.0.0.1", 8484), Stop("Stop", "127.0.0.1", 8484);
    NetworkChannel Take("Take", "127.0.0.1", 8484), Ready("Ready", "127.0.0.1", 8484);

    Controller controller(&Path, &NewPath, &Img, &Start, &Stop, &Take, &Ready, &Finish);

    cout << "Модуль КОНТРОЛЛЕР\n\n";
    controller.start();
}
