#include "Manipulator.h"

void Manipulator::getTake()
{
	cout << "\nÌÀÍÈÏÓËßÒÎÐ .1_1: îæèäàíèå êîìàíäû îò Êîíòðîëëåðà...";

	TData data;
	Take->get(&data);

	cout << "\nÌÀÍÈÏÓËßÒÎÐ .1_2: ïîëó÷åíà êîìàíäà îò Êîíòðîëëåðà";
}

void Manipulator::sendReady()
{
	cout << "\nÌÀÍÈÏÓËßÒÎÐ .2: îòïðàâêà ñîîáùåíèÿ î çàâåðøåíèè ñáîðà ãðóíòà â Êîíòðîëëåð...";

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

		cout << "\nÌÀÍÈÏÓËßÒÎÐ: ñáîð ãðóíòà...";
		this_thread::sleep_for(chrono::milliseconds(10000));

		sendReady();

		cout << "\n";
	}
}
