#include "Mover.h"

void Mover::getStartMoving()
{
	cout << "\nÌÎÄÓËÜ ÏÅÐÅÄÂÈÆÅÍÈß .1_1: îæèäàíèå êîìàíäû îò Êîíòðîëëåðà...";

	TData data;
	Start->get(&data);

	cout << "\nÌÎÄÓËÜ ÏÅÐÅÄÂÈÆÅÍÈß .1_2: ïîëó÷åíà êîìàíäà îò Êîíòðîëëåðà";
}

void Mover::sendStopMoving()
{
	cout << "\nÌÎÄÓËÜ ÏÅÐÅÄÂÈÆÅÍÈß .2: îòïðàâêà ñîîáùåíèÿ î çàâåðøåíèè äâèæåíèÿ â Êîíòðîëëåð...";

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

		cout << "\nÌÎÄÓËÜ ÏÅÐÅÄÂÈÆÅÍÈß: äâèæåíèå...";
		this_thread::sleep_for(chrono::milliseconds(15000));

		sendStopMoving();
	}
}
