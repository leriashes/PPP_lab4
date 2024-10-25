#include "Controller.h"

Controller::Controller(TChannel* Path, TChannel* NewPath, TChannel* Img, TChannel* Start, TChannel* Stop, TChannel* Take, TChannel* Ready, TChannel* Finish)
{
	this->Path = Path;
	this->NewPath = NewPath;
	this->Finish = Finish;

	this->Img = Img;

	this->Start = Start;
	this->Stop = Stop;

	this->Take = Take;
	this->Ready = Ready;
}

void Controller::start()
{
	while (true)
	{
		bool path = getPathData();

		if (path)
		{
			bool obstacle = getCameraData();

			if (!obstacle)
			{
				sendStartMoving();
				getStopMoving();
			}

			sendStopData(obstacle);
		}
		else
		{
			sendTake();
			getReady();
			sendFinish();
		}
	}
}

bool Controller::getPathData()
{
	cout << "\n���������� .1_1: �������� ������� ����������...";

	TData data;
	Path->get(&data);

	if (data.getNumber() != 0)
	{
		cout << "\n���������� .1_2: �������� ������� - ���������� ��������";
		return true;
	}
	else
	{
		cout << "\n���������� .1_2: �������� ������� - ����� ���������� ����������, �������� �����";
		return false;
	}
}

bool Controller::getCameraData()
{
	cout << "\n���������� .2_1: �������� ����������� � ������...";

	TData data;
	Img->get(&data);

	if (data.getNumber() % 3 == 0)
	{
		cout << "\n���������� .2_2: �������� ����������� � ������ #" << data.getNumber() << " - ���������� �����������";
		return true;
	}
	else
	{
		cout << "\n���������� .2_2: �������� ����������� � ������ #" << data.getNumber() << " - ����������� ���";
		return false;
	}
}

void Controller::sendStartMoving()
{
	cout << "\n���������� .3: �������� ������� � ������ ������������...";

	TData data(0, 4, "5 ������");
	Start->put(data);
}

void Controller::getStopMoving()
{
	cout << "\n���������� .4_1: �������� ��������� � ���������� � ������ ������������...";

	TData data;
	Stop->get(&data);

	cout << "\n���������� .4_2: �������� ��������� � ���������� �������� � ������ ������������";
}

void Controller::sendStopData(bool obstacle)
{
	cout << "\n���������� .5: �������� ��������� �� ��������� � ���������...";

	TData data(obstacle, 4, "������������");
	NewPath->put(data);
}

void Controller::sendTake()
{
	cout << "\n���������� .6: �������� ������� '������ ���� ������' � �����������...";

	TData data(0, 4, "�������");
	Take->put(data);
}

void Controller::getReady()
{
	cout << "\n���������� .7_1: �������� ��������� � ���������� �� ������������...";

	TData data;
	Ready->get(&data);

	cout << "\n���������� .7_2: �������� ��������� � ���������� �� ������������";
}

void Controller::sendFinish()
{
	cout << "\n���������� .8: �������� ��������� � ���������� ������ � ���������������� ������...";

	TData data(0, 4, "���������");
	Finish->put(data);
}
