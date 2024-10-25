#pragma once
#include "MoonwalkerModule.h"

class Mover : public MoonwalkerModule
{
private:
	TChannel* Start;
	TChannel* Stop;

	void getStartMoving();
	void sendStopMoving();

public:
	Mover(TChannel* Start, TChannel* Stop);
	void start() override;
};
