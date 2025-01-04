#pragma once
#include "MoonwalkerModule.h"

class Camera : public MoonwalkerModule
{
private:
	NetworkChannel* Img;
	void sendData(int count);

public:
	Camera(NetworkChannel* channel);
	void start() override;
};

