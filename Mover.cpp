#include "Mover.h"

void Mover::getStartMoving()
{
	cout << "\n������ ������������ .1_1: �������� ������� �� �����������...";

	TData data;
	Start->get(&data);

	cout << "\n������ ������������ .1_2: �������� ������� �� �����������";
}

void Mover::sendStopMoving()
{
	cout << "\n������ ������������ .2: �������� ��������� � ���������� �������� � ����������...";

	TData data(0, 5);
	Stop->put(data);
}

Mover::Mover(TChannel* Start, TChannel* Stop)
{
	this->Start = Start;
	this->Stop = Stop;
}

void Mover::start()
{
	while (true)
	{
		getStartMoving();

		cout << "\n������ ������������: ��������...";
		this_thread::sleep_for(chrono::milliseconds(15000));

		sendStopMoving();
	}
}
