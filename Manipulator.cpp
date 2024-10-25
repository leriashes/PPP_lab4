#include "Manipulator.h"

void Manipulator::getTake()
{
	cout << "\nМАНИПУЛЯТОР .1_1: ожидание команды от Контроллера...";

	TData data;
	Take->get(&data);

	cout << "\nМАНИПУЛЯТОР .1_2: получена команда от Контроллера";
}

void Manipulator::sendReady()
{
	cout << "\nМАНИПУЛЯТОР .2: отправка сообщения о завершении сбора грунта в Контроллер...";

	TData data(0, 6, "грунт собран");
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

		cout << "\nМАНИПУЛЯТОР: сбор грунта...";
		this_thread::sleep_for(chrono::milliseconds(10000));

		sendReady();
	}
}
