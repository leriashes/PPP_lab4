#pragma once
#include "MoonwalkerModule.h"

class GPS : public MoonwalkerModule
{
private:
	NetworkChannel* Nav;
	void sendData(int count);

public:
	GPS(NetworkChannel* channel);
	void start() override;
};

