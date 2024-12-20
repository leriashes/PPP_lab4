#pragma once
#include "MoonwalkerModule.h"

class Tracker : public MoonwalkerModule
{
private:
	TChannel* Location;
	void getData(int count);

public:
	Tracker(TChannel* LocationChannel);
	void start() override;
};

