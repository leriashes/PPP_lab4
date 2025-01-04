#pragma once
#include "MoonwalkerModule.h"

class Mover : public MoonwalkerModule
{
private:
	NetworkChannel* Start;
	NetworkChannel* Stop;

	void getStartMoving();
	void sendStopMoving();

public:
	Mover(NetworkChannel* Start, NetworkChannel* Stop);
	void start() override;
};
