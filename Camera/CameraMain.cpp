#include <iostream>
#include "..\Camera.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Img("IMG", 4096);
    Camera camera(&Img);

    cout << "Модуль КАМЕРА\n\n";
    camera.start();
}
