#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "MoonwalkerModule.h"
using namespace std;

class Camera : public MoonwalkerModule
{
private:
	void sendData(int count);

public:
	void start() override;
};

