#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "MoonwalkerModule.h"
using namespace std;

class GPS : public MoonwalkerModule
{
private:
	TChannel* Nav;
	void sendData(int count);

public:
	GPS(TChannel* channel);
	void start() override;
};

