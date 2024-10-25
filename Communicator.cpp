#include "Communicator.h"

void Communicator::sendData(int count)
{
	cout << "\n���������������� ������ .1: �������� ����� ���������� #" << count << "...";

	TData data(count, 1, "����� ����������");
	NewPath->put(data);
}

void Communicator::getData()
{
	cout << "\n���������������� ������ .2_1: �������� ��������� � ���������� �� �����������...";

	TData data;
	Finish->get(&data);

	cout << "\n���������������� ������ .2_2: �������� ��������� � ���������� #" << data.getNumber();
}

Communicator::Communicator(TChannel* NavChannel, TChannel* ContrChannel)
{
	NewPath = NavChannel;
	Finish = ContrChannel;
}

void Communicator::start()
{
	int i = 0;

	while (i < 1)
	{
		sendData(i);
		getData();

		i++;
	}
}
