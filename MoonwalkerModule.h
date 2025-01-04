#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "NetworkChannel.h"
using namespace std;

class MoonwalkerModule
{
public:
    virtual void start() = 0;
};

