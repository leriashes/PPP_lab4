#pragma once
#include "MoonwalkerModule.h"

class GPS : public MoonwalkerModule
{
private:
	TChannel* Nav;
	void sendData(int count);

public:
	GPS(TChannel* channel);
	void start() override;
};

