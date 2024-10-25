#include "Navigator.h"

void Navigator::getGPSData()
{
	cout << "\nНАВИГАТОР: ожидание местоположения от GPS...";

	TData data;
	Nav->get(&data);

	cout << "\nНАВИГАТОР: получено местоположение #" << data.getNumber();
}

Navigator::Navigator(TChannel* GPSchannel)
{
	Nav = GPSchannel;
}

void Navigator::start()
{
	while (true)
	{
		getGPSData();
	}
}
