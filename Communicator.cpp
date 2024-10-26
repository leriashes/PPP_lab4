#include "Communicator.h"

void Communicator::sendData(int count)
{
	cout << "\n\nÊÎÌÌÓÍÈÊÀÖÈÎÍÍÛÉ ÌÎÄÓËÜ .1: îòïðàâêà òî÷êè íàçíà÷åíèÿ #" << count << "...";

	TData data(count, 1);
	NewPath->put(data);
}

void Communicator::getData(int count)
{
	cout << "\nÊÎÌÌÓÍÈÊÀÖÈÎÍÍÛÉ ÌÎÄÓËÜ .2_1: îæèäàíèå ñîîáùåíèÿ î çàâåðøåíèè îò Êîíòðîëëåðà...";

	TData data;
	Finish->get(&data);

	cout << "\nÊÎÌÌÓÍÈÊÀÖÈÎÍÍÛÉ ÌÎÄÓËÜ .2_2: ïîëó÷åíî ñîîáùåíèå î çàâåðøåíèè ìèññèè #" << count << "\n";
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
