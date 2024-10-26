#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\n��������� .1_1: �������� ����� ����������...";

	TData data;
	NewPath->get(&data);

	if (data.getModuleNumber() == 1)
	{
		cout << "\n��������� .1_2: �������� ����� ���������� #" << data.getNumber();

		len = rand() % 3 + 1;
	}
	else
	{
		if (data.getNumber() == 1)
		{
			cout << "\n��������� .1_2: �������� ��������� �� �����������: ����������� - ���������� ����������� �������";
		}
		else
		{
			cout << "\n��������� .1_2: �������� ��������� �� �����������: ���������� �������� �� ��������";
			len -= 1;
		}
	}
}

void Navigator::getGPSData()
{
	cout << "\n��������� .2_1: �������� �������������� �� GPS...";

	TData data;
	Nav->get(&data);

	cout << "\n��������� .2_2: �������� �������������� #" << data.getNumber();
}

void Navigator::sendData()
{
	cout << "\n��������� .3: �������� �������� �� ����������... (�������� �������� : " << len << ")";

	TData data(len, 3);
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
		//this_thread::sleep_for(chrono::milliseconds(10000));
		
		sendData();

		cout << "\n";
	}
}
