#include <iostream>
#include <windows.h>
#include "GPS.h"
#include "Navigator.h"
#include "Tracker.h"
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
    Navigator navigator1(4, &Nav, &Coords, &Path), navigator2(5, &Nav, &Coords, &Path);
    Tracker tracker1(1, &Coords), tracker2(2, &Coords), tracker3(3, &Coords);


    ThreadWrap gpsThread(&gps);
    gpsThread.startThread();

    this_thread::sleep_for(chrono::milliseconds(20));

    ThreadWrap navigator1Thread(&navigator1), navigator2Thread(&navigator2);
    navigator1Thread.startThread();
    navigator2Thread.startThread();

    ThreadWrap tracker1Thread(&tracker1);
    tracker1Thread.startThread();
    ThreadWrap tracker2Thread(&tracker2);
    tracker2Thread.startThread();
    ThreadWrap tracker3Thread(&tracker3);
    tracker3Thread.startThread();

    navigator1Thread.waitForThread();
    navigator2Thread.waitForThread();
    gpsThread.waitForThread();
    tracker1Thread.waitForThread();
    tracker2Thread.waitForThread();
    tracker3Thread.waitForThread();

    return 0;
}
