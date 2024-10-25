#include "Camera.h"

void Camera::sendData(int count)
{
	cout << "\nÊÀÌÅĞÀ: îòïğàâêà ñíèìêà #" << count<< "...";

	TData data(count, 7, "ñíèìîê");
	Img->put(data);

	cout << "\nÊÀÌÅĞÀ: îòïğàâêà ñíèìêà #" << count << " âûïîëíåíà";
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
