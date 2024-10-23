#include "Camera.h"

void Camera::sendData(int count)
{
	cout << "\nÊÀÌÅÐÀ: îòïðàâêà ñíèìêà #" << count;
}

void Camera::start()
{
	int count = 0;

	while (true)
	{
		sendData(count++);
		this_thread::sleep_for(chrono::milliseconds(1500));
	}
}
