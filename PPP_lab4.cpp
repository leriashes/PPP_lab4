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

    Camera camera;
    Communicator communicator;
    Controller controller;
    GPS gps;
    Manipulator manipulator;
    Mover mover;
    Navigator navigator;

    ThreadWrap<GPS> gpsThread(&gps);
    gpsThread.startThread();

    ThreadWrap<Camera> cameraThread(&camera);
    cameraThread.startThread();

    gpsThread.waitForThread();
    cameraThread.waitForThread();

    return 0;
}
