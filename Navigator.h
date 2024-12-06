#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	CVChannel* Nav;
	TChannel* Coords;
	TChannel* Path;
	TChannel* Location;

	int location;
	int num;

	int getQueryData();
	void getGPSData();
	void sendPath();
	void sendLocation();

public:
	Navigator(CVChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel, TChannel* TrackerChannel);
	Navigator(int num, CVChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel, TChannel* TrackerChannel);
	void start() override;
};

