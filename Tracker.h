#pragma once
#include "MoonwalkerModule.h"

class Tracker : public MoonwalkerModule
{
private:
	int num;
	TChannel* Location;
	void getData(int count);

public:
	Tracker(TChannel* LocationChannel);
	Tracker(int num, TChannel* LocationChannel);
	void start() override;
};

