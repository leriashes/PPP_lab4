#include <iostream>
#include <windows.h>
#include "GPS.h"
#include "Controller.h"
#include "GPS.h"
#include "Manipulator.h"
#include "Mover.h"
#include "Navigator.h"
#include "ThreadWrap.h"
#include "TEstafeta.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "rus");

    TEstafeta Coords("Coords", 1024);

    TReliableChannel Nav("Nav", 1024);
    TReliableChannel Path("Path", 1024);

    GPS gps(&Coords);
    Navigator navigator1(1, &Nav, &Coords, &Path), navigator2(2, &Nav, &Coords, &Path);
    Tracker tracker1(&Coords), tracker2(&Coords), tracker3(&Coords);

    ThreadWrap navigator1Thread(&navigator1), navigator2Thread(&navigator2);
    navigator1Thread.startThread();
    navigator2Thread.startThread();

    ThreadWrap gpsThread(&gps);
    gpsThread.startThread();

    ThreadWrap manipulatorThread(&manipulator);
    manipulatorThread.startThread();

    navigator1Thread.waitForThread();
    navigator2Thread.waitForThread();
    gpsThread.waitForThread();
    tracker1Thread.waitForThread();
    tracker2Thread.waitForThread();
    tracker3Thread.waitForThread();

    return 0;
}
