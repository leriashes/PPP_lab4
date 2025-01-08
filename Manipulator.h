#pragma once
#include "MoonwalkerModule.h"

class Manipulator : public MoonwalkerModule
{
private:
	TChannel* Take;
	TChannel* Ready;
	int num;

	void getTake();
	void sendReady();

public:
	Manipulator(TChannel* Take, TChannel* Ready, int num);
	void start() override;
};

