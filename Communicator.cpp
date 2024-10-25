#include "Communicator.h"

void Communicator::sendData(int count)
{
	cout << "\nÊÎÌÌÓÍÈÊÀÖÈÎÍÍÛÉ ÌÎÄÓËÜ .1: îòïðàâêà òî÷êè íàçíà÷åíèÿ #" << count << "...";

	TData data(count, 1, "òî÷êà íàçíà÷åíèÿ");
	NewPath->put(data);
}

void Communicator::getData()
{
	cout << "\nÊÎÌÌÓÍÈÊÀÖÈÎÍÍÛÉ ÌÎÄÓËÜ .2_1: îæèäàíèå ñîîáùåíèÿ î çàâåðøåíèè îò Êîíòðîëëåðà...";

	TData data;
	Finish->get(&data);

	cout << "\nÊÎÌÌÓÍÈÊÀÖÈÎÍÍÛÉ ÌÎÄÓËÜ .2_2: ïîëó÷åíî ñîîáùåíèÿ î çàâåðøåíèè #" << data.getNumber();
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
