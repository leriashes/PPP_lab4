#pragma once
#include <iostream>
using namespace std;

class TData
{
private:
	int number;
	int moduleNumber;
	string data;

public:
	TData(int number, int moduleNumber, string data);
	
	int getNumber();
	int getModuleNumber();
	string getData();

	TData() = default;
};

