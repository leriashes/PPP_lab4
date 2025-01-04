#pragma once
#include "MoonwalkerModule.h"

class Communicator : public MoonwalkerModule
{
private:
	NetworkChannel* NewPath;
	NetworkChannel* Finish;

	void sendData(int count);
	void getData(int count);

public:
	Communicator(NetworkChannel* NavChannel, NetworkChannel* ContrChannel);
	void start() override;
};

