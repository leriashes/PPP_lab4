#pragma once
#include "MoonwalkerModule.h"

class Controller : public MoonwalkerModule
{
private:
	NetworkChannel* Path;
	NetworkChannel* NewPath;
	NetworkChannel* Finish;

	NetworkChannel* Img; 

	NetworkChannel* Start; 
	NetworkChannel* Stop;

	NetworkChannel* Take;
	NetworkChannel* Ready;

	bool getPathData();
	bool getCameraData();

	void sendStartMoving();
	void getStopMoving();
	void sendStopData(bool obstacle);
	void sendTake();
	void getReady();
	void sendFinish();

public:
	Controller(NetworkChannel* Path, NetworkChannel* NewPath, NetworkChannel* Img, NetworkChannel* Start, NetworkChannel* Stop, NetworkChannel* Take, NetworkChannel* Ready, NetworkChannel* Finish);
	void start() override;
};

