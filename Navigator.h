#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	TChannel* Nav;
	TChannel* Coords;
	TChannel* Path;
	TChannel* Location;

	int len;
	int location;

	bool getQueryData();
	void getGPSData();
	void sendPath();
	void sendLocation();

public:
	Navigator(TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel, TChannel* TrackerChannel);
	void start() override;
};

