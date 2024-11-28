#include "Navigator.h"

bool Navigator::getQueryData()
{
	if (num)
	{
		cout << "\n" << num << " НАВИГАТОР .1_1: ожидание...";
	}
	else
	{
		cout << "\nНАВИГАТОР .1_1: ожидание...";
	}
	

	TData data;
	Nav->get(&data);

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

		len = rand() % 3 + 1;
	}
	else if (data.getModuleNumber() == 8)
	{
		if (num)
		{
			cout << "\n" << num << " НАВИГАТОР .1_2: получен запрос на текущее местоположение #" << data.getNumber();
		}
		else
		{
			cout << "\nНАВИГАТОР .1_2: получен запрос на текущее местоположение #" << data.getNumber();
		}

		return false;
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
			
			len -= 1;
		}
	}

	return true;
}

void Navigator::getGPSData()
{
	if (num)
	{
		cout << "\n" << num << " НАВИГАТОР .2_1: ожидание местоположения от GPS...";
	}
	else
	{
		cout << "\nНАВИГАТОР .2_1: ожидание местоположения от GPS...";
	}

	TData data;
	Coords->get(&data);

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
		cout << "\n" << num << " НАВИГАТОР .3: отправка маршрута на Контроллер... (отрезков осталось : " << len << ")";
	}
	else
	{
		cout << "\nНАВИГАТОР .3: отправка маршрута на Контроллер... (отрезков осталось : " << len << ")";
	}

	TData data(len, 3);
	Path->put(data);
}

void Navigator::sendLocation()
{
	if (num)
	{
		cout << "\n" << num << " НАВИГАТОР .4: отправка текущего местоположения в модуль отслеживания...";
	}
	else
	{
		cout << "\nНАВИГАТОР .4: отправка текущего местоположения в модуль отслеживания...";
	}

	TData data(location, 3);
	Location->put(data);
}

Navigator::Navigator(TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel, TChannel* TrackerChannel)
{
	Nav = channel;
	Coords = GPSchannel;
	Path = ContrChannel;
	Location = TrackerChannel;
	this->num = 0;
}

Navigator::Navigator(int num, TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel, TChannel* TrackerChannel)
{
	Nav = channel;
	Coords = GPSchannel;
	Path = ContrChannel;
	Location = TrackerChannel;
	this->num = num;
}

void Navigator::start()
{
	while (true)
	{
		bool path = getQueryData();
		getGPSData();

		if (path)
		{
			if (num)
			{
				cout << "\n" << num << " НАВИГАТОР: построение маршрута...";
			}
			else
			{
				cout << "\nНАВИГАТОР: построение маршрута...";
			}
			
			this_thread::sleep_for(chrono::milliseconds(10000));

			sendPath();
		}
		else
		{
			sendLocation();
		}

		cout << "\n";
	}
}
