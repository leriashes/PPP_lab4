#include "Camera.h"

void Camera::sendData(int count)
{
	TData data(count, 7, "������");
	Img->put(data);

	cout << "\n    ������: ��������� ������ #" << count;
}

Camera::Camera(TChannel* channel)
{
	Img = channel;
}

void Camera::start()
{
	int count = 0;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}
