#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "TReliableChannel.h"
using namespace std;

class MoonwalkerModule
{
public:
    virtual void start() = 0;
};

