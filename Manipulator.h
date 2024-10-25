#pragma once
#include "MoonwalkerModule.h"

class Manipulator : public MoonwalkerModule
{
private:
	TChannel* Take;
	TChannel* Ready;

	void getTake();
	void sendReady();

public:
	Manipulator(TChannel* Take, TChannel* Ready);
	void start() override;
};

