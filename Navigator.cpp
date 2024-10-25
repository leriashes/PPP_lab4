#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\nНАВИГАТОР .1_1: ожидание точки назначения...";

	TData data;
	NewPath->get(&data);

	if (data.getModuleNumber() == 1)
	{
		cout << "\nНАВИГАТОР .1_2: получена точка назначения #" << data.getNumber();
	}
	else
	{
		if (data.getNumber() == 1)
		{
			cout << "\nНАВИГАТОР .1_2: точка назначения #" << data.getNumber() << ", препятствие - необходимо перестроить маршрут";
		}
		else
		{
			cout << "\nНАВИГАТОР .1_2: точка назначения #" << data.getNumber() << ", продолжить движение по маршруту";
		}
	}
}

void Navigator::getGPSData()
{
	cout << "\nНАВИГАТОР .2_1: ожидание местоположения от GPS...";

	TData data;
	Nav->get(&data);

	cout << "\nНАВИГАТОР .2_2: получено местоположение #" << data.getNumber();
}

void Navigator::sendData()
{
	cout << "\nНАВИГАТОР .3: отправка маршрута на Контроллер...";

	TData data(0, 1, "точка назначения");
	Path->put(data);
}

Navigator::Navigator(TChannel* CommunicatorChannel, TChannel* GPSChannel, TChannel* ContrChannel)
{
	NewPath = CommunicatorChannel;
	Nav = GPSChannel;
	Path = ContrChannel;
}

void Navigator::start()
{
	while (true)
	{
		getPathData();
		getGPSData();
		
		cout << "\nНАВИГАТОР: построение маршрута...";
		this_thread::sleep_for(chrono::milliseconds(10000));

		sendData();
	}
}
