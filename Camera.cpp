#include "Camera.h"

void Camera::sendData(int count)
{
	TData data(count, 7);
	Img->put(data);

	cout << "\n    ÊÀÌÅĞÀ: îòïğàâëåí ñíèìîê #" << count;
}

Camera::Camera(TChannel* channel)
{
	Img = channel;
}

void Camera::start()
{
	int count = 1;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
