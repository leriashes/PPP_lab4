#include "Navigator.h"

void Navigator::getPathData()
{
	cout << "\nНАВИГАТОР .1: ожидание точки назначения...";

	TData data;
	NewPath->get(&data);

	cout << "\nНАВИГАТОР .1: получена точка назначения #" << data.getNumber();
}

void Navigator::getGPSData()
{
	cout << "\nНАВИГАТОР .2: ожидание местоположения от GPS...";

	TData data;
	Nav->get(&data);

	cout << "\nНАВИГАТОР .2: получено местоположение #" << data.getNumber();
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
