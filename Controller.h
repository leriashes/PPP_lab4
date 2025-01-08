#pragma once
#include "MoonwalkerModule.h"

class Controller : public MoonwalkerModule
{
private:
	int num;
	TSemaphore* print;
	TSemaphore* free;

	TChannel* Take1;
	TChannel* Ready1;
	TChannel* Take2;
	TChannel* Ready2;

	TChannel* service;

	void sendTake();
	void getReady();

public:
	Controller(int num, TSemaphore* print, TSemaphore* free, TChannel* service, TChannel* Take1, TChannel* Ready1, TChannel* Take2, TChannel* Ready2);
	void start() override;
};

