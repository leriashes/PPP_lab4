#include "GPS.h"

void GPS::sendData(int count)
{
	cout << "\n  GPS: буду отправлять местоположение #" << count;

	TData data(count, 3);
	Nav->put(data, 1);

	cout << "\n  GPS: отправлено местоположение #" << count;
}

GPS::GPS(TChannel* channel)
{
	Nav = channel;
}

void GPS::start()
{
	int count = 1;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}
