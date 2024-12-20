#include "Tracker.h"

void Tracker::getData(int count)
{
	cout << "\n" << num << " ÌÎÄÓËÜ ÎÒÑËÅÆÈÂÀÍÈß .1_1: îæèäàíèå êîîðäèíàò îò GPS...";

	TData data;
	Location->get(&data, num);

	cout << "\n" << num << " ÌÎÄÓËÜ ÎÒÑËÅÆÈÂÀÍÈß .1_2: ïîëó÷åíû êîîðäèíàòû #" << count << " (òåêóùåå ìåñòîïîëîæåíèå: #" << data.getNumber() << ")\n";
}

Tracker::Tracker(TChannel* LocationChannel)
{
	num = 1;
	Location = LocationChannel;
}

Tracker::Tracker(int num, TChannel* LocationChannel)
{
	this->num = num;
	Location = LocationChannel;
}

void Tracker::start()
{
	int i = 1;

	while (i < 20)
	{
		getData(i);

		this_thread::sleep_for(chrono::milliseconds(400 * num));
		i++;
	}
}
