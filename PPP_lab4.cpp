#include <iostream>
#include "Camera.h"
#include "Communicator.h"
#include "Controller.h"
#include "GPS.h"
#include "Manipulator.h"
#include "Mover.h"
#include "Navigator.h"
#include "ThreadWrap.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Nav;
    TChannel Img;

    Camera camera(&Img);
    Communicator communicator;
    Controller controller;
    GPS gps(&Nav);
    Manipulator manipulator;
    Mover mover;
    Navigator navigator;


    ThreadWrap gpsThread(&gps);
    gpsThread.startThread();

    ThreadWrap cameraThread(&camera);
    cameraThread.startThread();

    gpsThread.waitForThread();
    cameraThread.waitForThread();

    return 0;
}
