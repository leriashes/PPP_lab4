#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "TReliableChannel.h"
#include "CVChannel.h"
using namespace std;

class MoonwalkerModule
{
public:
    virtual void start() = 0;
};

