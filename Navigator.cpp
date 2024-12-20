#include "Navigator.h"

void Navigator::getQueryData()
{
	if (num)
	{
		cout << "\n" << num << " НАВИГАТОР .1_1: ожидание точки назначения от коммуникационного модуля...";
	}
	else
	{
		cout << "\nНАВИГАТОР .1_1: ожидание точки назначения от коммуникационного модуля...";
	}


	TData data;
	Nav->get(&data, num);

	if (data.getModuleNumber() == 1)
	{
		if (num)
		{
			cout << "\n" << num << " НАВИГАТОР .1_2: получена точка назначения #" << data.getNumber();
		}
		else
		{
			cout << "\nНАВИГАТОР .1_2: получена точка назначения #" << data.getNumber();
		}
	}
	else
	{
		if (data.getNumber() == 1)
		{
			if (num)
			{
				cout << "\n" << num << " НАВИГАТОР .1_2: получено сообщение от Контроллера: препятствие - необходимо перестроить маршрут";
			}
			else
			{
				cout << "\nНАВИГАТОР .1_2: получено сообщение от Контроллера: препятствие - необходимо перестроить маршрут";
			}
		}
		else
		{
			if (num)
			{
				cout << "\n" << num << " НАВИГАТОР .1_2: получено сообщение от Контроллера: продолжить движение по маршруту";
			}
			else
			{
				cout << "\nНАВИГАТОР .1_2: получено сообщение от Контроллера: продолжить движение по маршруту";
			}
		}
	}
}

void Navigator::getGPSData()
{
	cout << "\nНАВИГАТОР .2_1: ожидание местоположения от GPS...";

	TData data;
	Coords->get(&data, num);

	location = data.getNumber();

	if (num)
	{
		cout << "\n" << num << " НАВИГАТОР .2_2: получено местоположение #" << location;
	}
	else
	{
		cout << "\nНАВИГАТОР .2_2: получено местоположение #" << location;
	}
}

void Navigator::sendPath()
{
	if (num)
	{
		cout << "\n" << num << " НАВИГАТОР .3: отправка маршрута на Контроллер...";
	}
	else
	{
		cout << "\nНАВИГАТОР .3: отправка маршрута на Контроллер...";
	}

	TData data(rand() % 3, 3);
	Path->put(data);
}

Navigator::Navigator(TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel)
{
	Nav = channel;
	Coords = GPSchannel;
	Path = ContrChannel;
	this->num = 0;
}

Navigator::Navigator(int num, TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel)
{
	Nav = channel;
	Coords = GPSchannel;
	Path = ContrChannel;
	this->num = num;
}


void Navigator::start()
{
	while (true) {
		getQueryData();
		getGPSData();

		if (num)
		{
			cout << "\n" << num << " НАВИГАТОР: построение маршрута...";
		}
		else
		{
			cout << "\nНАВИГАТОР: построение маршрута...";
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		sendPath();

		cout << "\n";
	}
}
