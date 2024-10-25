#include "Navigator.h"

void Navigator::getGPSData()
{
	cout << "\n���������: �������� �������������� �� GPS...";

	TData data;
	Nav->get(&data);

	cout << "\n���������: �������� �������������� #" << data.getNumber();
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
