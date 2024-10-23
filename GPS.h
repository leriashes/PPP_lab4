#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "MoonwalkerModule.h"
using namespace std;

class GPS : public MoonwalkerModule
{
private:
	void sendData(int count);

public:
	void start() override;
};

