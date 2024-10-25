#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "TChannel.h"
using namespace std;

class MoonwalkerModule
{
public:
    virtual void start() = 0;
};

