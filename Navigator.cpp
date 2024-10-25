#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\nНАВИГАТОР .1: ожидание точки назначения...";

	TData data;
	NewPath->get(&data);

	if (data.getModuleNumber() == 1)
		version = 0;
	else
		version += 1;

	if (!version)
		cout << "\nНАВИГАТОР .1: получена точка назначения #" << data.getNumber();
	else
		cout << "\nНАВИГАТОР .1: получена точка назначения #" << data.getNumber() << ", необходимо перестроить маршрут";
}

void Navigator::getGPSData()
{
	cout << "\nНАВИГАТОР .2: ожидание местоположения от GPS...";

	TData data;
	Nav->get(&data);

	cout << "\nНАВИГАТОР .2: получено местоположение #" << data.getNumber();
}

void Navigator::sendData()
{
	cout << "\nНАВИГАТОР .3: отправка маршрута на Контроллер...";

	TData data(version, 1, "точка назначения");
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
