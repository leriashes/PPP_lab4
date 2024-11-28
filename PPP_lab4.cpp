#include <iostream>
#include "Camera.h"
#include "Communicator.h"
#include "Controller.h"
#include "GPS.h"
#include "Manipulator.h"
#include "Mover.h"
#include "Navigator.h"
#include "Tracker.h"
#include "ThreadWrap.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    TChannel Coords("Coords", 1024);
    TChannel Img("IMG", 1024);

    TReliableChannel Nav("Nav", 1024), Path("Path", 1024), Finish("Finish", 1024);
    TReliableChannel Start("Start", 1024), Stop("Stop", 1024);
    TReliableChannel Take("Take", 1024), Ready("Ready", 1024);
    TReliableChannel Location("Location", 1024);

    Camera camera(&Img);
    Communicator communicator(&Nav, &Finish);
    Controller controller(&Path, &Nav, &Img, &Start, &Stop, &Take, &Ready, &Finish);
    GPS gps(&Coords);
    Manipulator manipulator(&Take, &Ready);
    Mover mover(&Start, &Stop);
    Navigator navigator1(1, &Nav, &Coords, &Path, &Location), navigator2(2, &Nav, &Coords, &Path, &Location);
    Tracker tracker(&Nav, &Location);


    ThreadWrap gpsThread(&gps);
    gpsThread.startThread();

    ThreadWrap cameraThread(&camera);
    cameraThread.startThread();

    ThreadWrap navigator1Thread(&navigator1), navigator2Thread(&navigator2);
    navigator1Thread.startThread();
    navigator2Thread.startThread();

    ThreadWrap controllerThread(&controller);
    controllerThread.startThread();

    ThreadWrap communicatorThread(&communicator);
    communicatorThread.startThread();

    ThreadWrap manipulatorThread(&manipulator);
    manipulatorThread.startThread();

    ThreadWrap moverThread(&mover);
    moverThread.startThread();

    ThreadWrap trackerThread(&tracker);
    trackerThread.startThread();

    gpsThread.waitForThread();
    cameraThread.waitForThread();
    navigator1Thread.waitForThread();
    navigator2Thread.waitForThread();
    communicatorThread.waitForThread();
    controllerThread.waitForThread();
    manipulatorThread.waitForThread();
    moverThread.waitForThread();
    trackerThread.waitForThread();

    return 0;
}
