#include "Manipulator.h"

void Manipulator::getTake()
{
	cout << "\n" << num << " МАНИПУЛЯТОР .1_1: ожидание команды от Контроллера...";

	TData data;
	Take->get(&data);

	cout << "\n" << num << " МАНИПУЛЯТОР .1_2: получена команда от Контроллера";
}

void Manipulator::sendReady()
{
	cout << "\n" << num << " МАНИПУЛЯТОР .2: отправка сообщения о завершении сбора грунта в Контроллер...";

	TData data(0, 6);
	Ready->put(data);
}

Manipulator::Manipulator(TChannel* Take, TChannel* Ready, int num)
{
	this->Take = Take;
	this->Ready = Ready;
	this->num = num;
}

void Manipulator::start()
{
	while (true)
	{
		getTake();

		cout << "\n" << num << " МАНИПУЛЯТОР: сбор грунта...";
		this_thread::sleep_for(chrono::milliseconds(10000));

		sendReady();

		cout << "\n";
	}
}
