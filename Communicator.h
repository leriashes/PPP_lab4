#pragma once
#include "MoonwalkerModule.h"

class Communicator : public MoonwalkerModule
{
private:
	CVChannel* NewPath;
	TChannel* Finish;

	int sendData(int count);
	void getData(int count);

public:
	Communicator(CVChannel* NavChannel, TChannel* ContrChannel);
	void start() override;
};

