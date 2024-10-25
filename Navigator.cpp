#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\nНАВИГАТОР: ожидание точки назначения от Коммуникационного модуля...";

	TData data;
	NewPath->get(&data);

	cout << "\nНАВИГАТОР: получена точка назначения #" << data.getNumber();
}

void Navigator::getGPSData()
{
	cout << "\nНАВИГАТОР: ожидание местоположения от GPS...";

	TData data;
	Nav->get(&data);

	cout << "\nНАВИГАТОР: получено местоположение #" << data.getNumber();
}

Navigator::Navigator(TChannel* CommunicatorChannel, TChannel* GPSChannel)
{
	NewPath = CommunicatorChannel;
	Nav = GPSChannel;
}

void Navigator::start()
{
	while (true)
	{
		getPathData();
		getGPSData();
	}
}
