#pragma once
#include "MoonwalkerModule.h"

class Tracker : public MoonwalkerModule
{
private:
	CVChannel* Nav;
	TChannel* Location;

	int sendData(int count);
	void getData(int count);

public:
	Tracker(CVChannel* NavChannel, TChannel* LocationChannel);
	void start() override;
};

