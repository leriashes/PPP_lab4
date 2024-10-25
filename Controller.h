#pragma once
#include "MoonwalkerModule.h"

class Controller : public MoonwalkerModule
{
private:
	TChannel* Path;
	TChannel* NewPath;
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
	void sendStopData();
	void sendTake();
	void getReady();
	void sendFinish();

public:
	Controller(TChannel* Path, TChannel* NewPath, TChannel* Img, TChannel* Start, TChannel* Stop, TChannel* Take, TChannel* Ready, TChannel* Finish);
	void start() override;
};

