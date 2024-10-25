#include "Communicator.h"

void Communicator::sendData(int count)
{
	cout << "\n���������������� ������ .1: �������� ����� ���������� #" << count << "...";

	TData data(count, 1, "����� ����������");
	NewPath->put(data);

	cout << "\n���������������� ������ .1: �������� ����� ���������� #" << count << " ���������";
}

void Communicator::getData()
{
	cout << "\n���������������� ������ .2: �������� ��������� � ���������� �� �����������...";

	TData data;
	Finish->get(&data);

	cout << "\n���������������� ������ .2: �������� ��������� � ���������� #" << data.getNumber();
}

Communicator::Communicator(TChannel* NavChannel, TChannel* ContrChannel)
{
	NewPath = NavChannel;
	Finish = ContrChannel;
}

void Communicator::start()
{
	int i = 0;

	while (i < 5)
	{
		sendData(i);
		getData();

		i++;
	}
}
