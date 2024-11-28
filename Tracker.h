#pragma once
#include "MoonwalkerModule.h"

class Tracker : public MoonwalkerModule
{
private:
	TChannel* Nav;
	TChannel* Location;

	void sendData(int count);
	void getData(int count);

public:
	Tracker(TChannel* NavChannel, TChannel* LocationChannel);
	void start() override;
};

