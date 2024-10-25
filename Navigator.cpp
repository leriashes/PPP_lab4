#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\n���������: �������� ����� ���������� �� ����������������� ������...";

	TData data;
	NewPath->get(&data);

	cout << "\n���������: �������� ����� ���������� #" << data.getNumber();
}

void Navigator::getGPSData()
{
	cout << "\n���������: �������� �������������� �� GPS...";

	TData data;
	Nav->get(&data);

	cout << "\n���������: �������� �������������� #" << data.getNumber();
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
