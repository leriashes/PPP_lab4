#include <iostream>
#include "..\Camera.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    NetworkChannel Img("IMG", "127.0.0.1", 8484, false);
    Camera camera(&Img);

    cout << "Модуль КАМЕРА\n\n";
    camera.start();
}
