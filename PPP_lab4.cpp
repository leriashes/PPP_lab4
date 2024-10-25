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

    TReliableChannel NewPath, Path, Finish;
    TReliableChannel Start, Stop;
    TReliableChannel Take, Ready;

    Camera camera(&Img);
    Communicator communicator(&NewPath, &Finish);
    Controller controller(&Path, &NewPath, &Img, &Start, &Stop, &Take, &Ready, &Finish);
    GPS gps(&Nav);
    Manipulator manipulator(&Take, &Ready);
    Mover mover;
    Navigator navigator(&NewPath, &Nav, &Path);


    ThreadWrap gpsThread(&gps);
    gpsThread.startThread();

    ThreadWrap cameraThread(&camera);
    cameraThread.startThread();

    ThreadWrap navigatorThread(&navigator);
    navigatorThread.startThread();

    ThreadWrap controllerThread(&controller);
    controllerThread.startThread();

    ThreadWrap communicatorThread(&communicator);
    communicatorThread.startThread();

    ThreadWrap manipulatorThread(&manipulator);
    manipulatorThread.startThread();

    gpsThread.waitForThread();
    cameraThread.waitForThread();
    navigatorThread.waitForThread();
    communicatorThread.waitForThread();
    controllerThread.waitForThread();
    manipulatorThread.waitForThread();

    return 0;
}
