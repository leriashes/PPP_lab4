#include "GPS.h"

void GPS::sendData(int count)
{
	cout << "\nGPS: �������� �������������� #" << count;
}

void GPS::start()
{
	int count = 0;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(1500));
	}
}
