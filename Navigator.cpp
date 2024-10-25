#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\n��������� .1: �������� ����� ����������...";

	TData data;
	NewPath->get(&data);

	cout << "\n��������� .1: �������� ����� ���������� #" << data.getNumber();
}

void Navigator::getGPSData()
{
	cout << "\n��������� .2: �������� �������������� �� GPS...";

	TData data;
	Nav->get(&data);

	cout << "\n��������� .2: �������� �������������� #" << data.getNumber();
}

Navigator::Navigator(TChannel* CommunicatorChannel, TChannel* GPSChannel)
{
	NewPath = CommunicatorChannel;
	Nav = GPSChannel;
}

void Navigator::start()
{
	while (true)
	{
		getPathData();
		getGPSData();
	}
}
