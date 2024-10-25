#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "MoonwalkerModule.h"
using namespace std;

class Camera : public MoonwalkerModule
{
private:
	TChannel* Img;
	void sendData(int count);

public:
	Camera(TChannel* channel);
	void start() override;
};

