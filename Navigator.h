#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	TChannel* NewPath;
	TChannel* Nav;
	TChannel* Path;

	int version;

	void getPathData();
	void getGPSData();
	void sendData();

public:
	Navigator(TChannel* CommunicatorChannel, TChannel* GPSchannel, TChannel* ContrChannel);
	void start() override;
};

