#pragma once
#include "MoonwalkerModule.h"

class Communicator : public MoonwalkerModule
{
private:
	TChannel* NewPath;
	TChannel* Finish;

	void sendData(int count);
	void getData();

public:
	Communicator(TChannel* NavChannel, TChannel* ContrChannel);
	void start() override;
};

