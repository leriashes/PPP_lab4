#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\n��������� .1: �������� ����� ����������...";

	TData data;
	NewPath->get(&data);

	if (data.getModuleNumber() == 1)
		version = 0;
	else
		version += 1;

	if (!version)
		cout << "\n��������� .1: �������� ����� ���������� #" << data.getNumber();
	else
		cout << "\n��������� .1: �������� ����� ���������� #" << data.getNumber() << ", ���������� ����������� �������";
}

void Navigator::getGPSData()
{
	cout << "\n��������� .2: �������� �������������� �� GPS...";

	TData data;
	Nav->get(&data);

	cout << "\n��������� .2: �������� �������������� #" << data.getNumber();
}

void Navigator::sendData()
{
	cout << "\n��������� .3: �������� �������� �� ����������...";

	TData data(version, 1, "����� ����������");
	Path->put(data);
}

Navigator::Navigator(TChannel* CommunicatorChannel, TChannel* GPSChannel, TChannel* ContrChannel)
{
	NewPath = CommunicatorChannel;
	Nav = GPSChannel;
	Path = ContrChannel;
}

void Navigator::start()
{
	while (true)
	{
		getPathData();
		getGPSData();
		
		cout << "\n���������: ���������� ��������...";
		this_thread::sleep_for(chrono::milliseconds(10000));

		sendData();
	}
}
