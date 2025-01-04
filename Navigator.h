#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	NetworkChannel* NewPath;
	NetworkChannel* Nav;
	NetworkChannel* Path;

	int len;

	void getPathData();
	void getGPSData();
	void sendData();

public:
	Navigator(NetworkChannel* CommunicatorChannel, NetworkChannel* GPSchannel, NetworkChannel* ContrChannel);
	void start() override;
};

