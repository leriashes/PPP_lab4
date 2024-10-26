#include "Communicator.h"

void Communicator::sendData(int count)
{
	cout << "\n\n���������������� ������ .1: �������� ����� ���������� #" << count << "...";

	TData data(count, 1);
	NewPath->put(data);
}

void Communicator::getData(int count)
{
	cout << "\n���������������� ������ .2_1: �������� ��������� � ���������� �� �����������...";

	TData data;
	Finish->get(&data);

	cout << "\n���������������� ������ .2_2: �������� ��������� � ���������� ������ #" << count << "\n";
}

Communicator::Communicator(TChannel* NavChannel, TChannel* ContrChannel)
{
	NewPath = NavChannel;
	Finish = ContrChannel;
}

void Communicator::start()
{
	int i = 1;

	while (i < 10)
	{
		sendData(i);
		getData(i);

		i++;
	}
}
