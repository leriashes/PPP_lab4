#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	TChannel* NewPath;
	TChannel* Nav;

	void getPathData();
	void getGPSData();

public:
	Navigator(TChannel* CommunicatorChannel, TChannel* GPSchannel);
	void start() override;
};

