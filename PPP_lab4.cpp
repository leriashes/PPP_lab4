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

    TReliableChannel NewPath;
    TReliableChannel Path;
    TReliableChannel Finish;

    Camera camera(&Img);
    Communicator communicator(&NewPath, &Finish);
    Controller controller;
    GPS gps(&Nav);
    Manipulator manipulator;
    Mover mover;
    Navigator navigator(&NewPath, &Nav, &Path);


    ThreadWrap gpsThread(&gps);
    gpsThread.startThread();

    ThreadWrap cameraThread(&camera);
    cameraThread.startThread();

    ThreadWrap navigatorThread(&navigator);
    navigatorThread.startThread();

    ThreadWrap communicatorThread(&communicator);
    communicatorThread.startThread();

    gpsThread.waitForThread();
    cameraThread.waitForThread();
    navigatorThread.waitForThread();
    communicatorThread.waitForThread();

    return 0;
}
