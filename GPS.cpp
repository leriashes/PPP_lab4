#include "GPS.h"

void GPS::sendData(int count)
{
	cout << "\nGPS: отправка местоположения #" << count << "...";

	TData data(count, 3, "текущее местоположение");
	Nav->put(data);

	cout << "\nGPS: отправка местоположения #" << count << " выполнена";
}

GPS::GPS(TChannel* channel)
{
	Nav = channel;
}

void GPS::start()
{
	int count = 0;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(5000));
	}
}
