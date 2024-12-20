#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	TChannel* Nav;
	TChannel* Coords;
	TChannel* Path;

	int location;
	int num;

	void getQueryData();
	void getGPSData();
	void sendPath();

public:
	Navigator(TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel);
	Navigator(int num, TChannel* channel, TChannel* GPSchannel, TChannel* ContrChannel);
	void start() override;
};

