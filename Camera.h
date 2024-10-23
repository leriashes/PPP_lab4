#pragma once
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

class Camera
{
private:
	void sendData(int count);

public:

	Camera() = default;

	void start();
};

