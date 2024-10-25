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

    TChannel Nav("NAV", 1024);
    TChannel Img("IMG", 1024);

    TReliableChannel NewPath("NewPath", 1024), Path("Path", 1024), Finish("Finish", 1024);
    TReliableChannel Start("Start", 1024), Stop("Stop", 1024);
    TReliableChannel Take("Take", 1024), Ready("Ready", 1024);

    Camera camera(&Img);
    Communicator communicator(&NewPath, &Finish);
    Controller controller(&Path, &NewPath, &Img, &Start, &Stop, &Take, &Ready, &Finish);
    GPS gps(&Nav);
    Manipulator manipulator(&Take, &Ready);
    Mover mover(&Start, &Stop);
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

    ThreadWrap moverThread(&mover);
    moverThread.startThread();

    gpsThread.waitForThread();
    cameraThread.waitForThread();
    navigatorThread.waitForThread();
    communicatorThread.waitForThread();
    controllerThread.waitForThread();
    manipulatorThread.waitForThread();
    moverThread.waitForThread();

    return 0;
}
