#pragma once
#include "MoonwalkerModule.h"

class Controller : public MoonwalkerModule
{
private:
	TChannel* Path;
	CVChannel* NewPath;
	TChannel* Finish;

	TChannel* Img; 

	TChannel* Start; 
	TChannel* Stop;

	TChannel* Take;
	TChannel* Ready;

	bool getPathData();
	bool getCameraData();

	void sendStartMoving();
	void getStopMoving();
	int sendStopData(bool obstacle);
	void sendTake();
	void getReady();
	void sendFinish();

public:
	Controller(TChannel* Path, CVChannel* NewPath, TChannel* Img, TChannel* Start, TChannel* Stop, TChannel* Take, TChannel* Ready, TChannel* Finish);
	void start() override;
};

