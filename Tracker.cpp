#include "Tracker.h"

void Tracker::sendData(int count)
{
	cout << "\n\nÌÎÄÓËÜ ÎÒÑËÅÆÈÂÀÍÈß .1: îòïğàâêà çàïğîñà íà òåêóùåå ìåñòîïîëîæåíèå ëóíîõîäà #" << count << "...";

	TData data(count, 8);
	Nav->put(data);
}

void Tracker::getData(int count)
{
	cout << "\nÌÎÄÓËÜ ÎÒÑËÅÆÈÂÀÍÈß .2_1: îæèäàíèå îòâåòà íà çàïğîñ îò Íàâèãàòîğà...";

	TData data;
	Location->get(&data);

	cout << "\nÌÎÄÓËÜ ÎÒÑËÅÆÈÂÀÍÈß .2_2: ïîëó÷åí îòâåò #" << count << " (òåêóùåå ìåñòîïîëîæåíèå: #" << data.getNumber() << ")\n";
}

Tracker::Tracker(TChannel* NavChannel, TChannel* LocationChannel)
{
	Nav = NavChannel;
	Location = LocationChannel;
}

void Tracker::start()
{
	int i = 1;

	while (i < 11)
	{
		sendData(i);
		getData(i);

		this_thread::sleep_for(chrono::milliseconds(5000));
		i++;
	}
}
