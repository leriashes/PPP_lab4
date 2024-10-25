#include "TData.h"

TData::TData(int number, int moduleNumber)
{
	this->number = number;
	this->moduleNumber = moduleNumber;
}

int TData::getNumber()
{
	return this->number;
}

int TData::getModuleNumber()
{
	return this->moduleNumber;
}
