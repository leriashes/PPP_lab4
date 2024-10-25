#include "Communicator.h"

void Communicator::sendData(int count)
{
	cout << "\n���������������� ������: �������� ����� ���������� #" << count << "...";

	TData data(count, 1, "����� ����������");
	NewPath->put(data);

	cout << "\n���������������� ������: �������� ����� ���������� #" << count << " ���������";
}

void Communicator::getData()
{
	cout << "\n���������������� ������: �������� ��������� � ���������� �� �����������...";

	TData data;
	Finish->get(&data);

	cout << "\n���������������� ������: �������� ��������� � ���������� #" << data.getNumber();
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
