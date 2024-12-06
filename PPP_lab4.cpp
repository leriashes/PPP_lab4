#include <iostream>
#include <windows.h>
#include "Communicator.h"
#include "Controller.h"
#include "Navigator.h"
#include "Tracker.h"
#include "ThreadWrap.h"
#include "CVChannel.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    InitializeConditionVariable(&BufferNotEmpty);
    InitializeConditionVariable(&BufferNotFull);
    InitializeCriticalSection(&BufferLock);

    TChannel Coords("Coords", 1024);
    TChannel Img("IMG", 1024);

    CVChannel Nav;

    TReliableChannel Path("Path", 1024), Finish("Finish", 1024), Start("Start", 1024), Stop("Stop", 1024);
    TReliableChannel Take("Take", 1024), Ready("Ready", 1024);
    TReliableChannel Location("Location", 1024);

    Communicator communicator(&Nav, &Finish);
    Controller controller(&Path, &Nav, &Img, &Start, &Stop, &Take, &Ready, &Finish);
    Navigator navigator1(1, &Nav, &Coords, &Path, &Location), navigator2(2, &Nav, &Coords, &Path, &Location);
    Tracker tracker1(&Nav, &Location), tracker2(&Nav, &Location), tracker3(&Nav, &Location);

    ThreadWrap navigator1Thread(&navigator1), navigator2Thread(&navigator2);
    navigator1Thread.startThread();
    navigator2Thread.startThread();

    ThreadWrap controllerThread(&controller);
    controllerThread.startThread();

    ThreadWrap communicatorThread(&communicator);
    communicatorThread.startThread();

    ThreadWrap tracker1Thread(&tracker1);
    tracker1Thread.startThread();
    ThreadWrap tracker2Thread(&tracker2);
    tracker2Thread.startThread();
    ThreadWrap tracker3Thread(&tracker3);
    tracker3Thread.startThread();

    getchar();
    EnterCriticalSection(&BufferLock);
    StopRequested = TRUE;
    LeaveCriticalSection(&BufferLock);

    navigator1Thread.waitForThread();
    navigator2Thread.waitForThread();
    communicatorThread.waitForThread();
    controllerThread.waitForThread();
    tracker1Thread.waitForThread();

    return 0;
}
