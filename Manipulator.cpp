#include "Manipulator.h"

void Manipulator::getTake()
{
	cout << "\n����������� .1_1: �������� ������� �� �����������...";

	TData data;
	Take->get(&data);

	cout << "\n����������� .1_2: �������� ������� �� �����������";
}

void Manipulator::sendReady()
{
	cout << "\n����������� .2: �������� ��������� � ���������� ����� ������ � ����������...";

	TData data(0, 6);
	Ready->put(data);
}

Manipulator::Manipulator(TChannel* Take, TChannel* Ready)
{
	this->Take = Take;
	this->Ready = Ready;
}

void Manipulator::start()
{
	while (true)
	{
		getTake();

		cout << "\n�����������: ���� ������...";
		this_thread::sleep_for(chrono::milliseconds(10000));

		sendReady();

		cout << "\n";
	}
}
