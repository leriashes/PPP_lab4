#pragma once
#include "MoonwalkerModule.h"

class Camera : public MoonwalkerModule
{
private:
	TChannel* Img;
	void sendData(int count);

public:
	Camera(TChannel* channel);
	void start() override;
};

