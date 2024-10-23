#pragma once
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

class GPS
{
private:
	void sendData(int count);

public:

	GPS() = default;

	void start();
};

