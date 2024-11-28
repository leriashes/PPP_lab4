#include "GPS.h"

void GPS::sendData(int count)
{
	TData data(count, 3);
	Coords->put(data);

	cout << "\n    GPS: отправлено местоположение #" << count;
}

GPS::GPS(TChannel* channel)
{
	Coords = channel;
}

void GPS::start()
{
	int count = 1;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}
