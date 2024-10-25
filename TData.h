#pragma once
#include <iostream>
using namespace std;

class TData
{
private:
	int number;
	int moduleNumber;

public:
	TData(int number, int moduleNumber);
	
	int getNumber();
	int getModuleNumber();

	TData() = default;
};

