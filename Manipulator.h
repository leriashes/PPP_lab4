#pragma once
#include "MoonwalkerModule.h"

class Manipulator : public MoonwalkerModule
{
private:
	NetworkChannel* Take;
	NetworkChannel* Ready;

	void getTake();
	void sendReady();

public:
	Manipulator(NetworkChannel* Take, NetworkChannel* Ready);
	void start() override;
};

