#pragma once
#include "MoonwalkerModule.h"

class Navigator : public MoonwalkerModule
{
private:
	TChannel* Nav;
	void getGPSData();

public:
	Navigator(TChannel* GPSchannel);
	void start() override;
};

