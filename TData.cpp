#include "TData.h"

TData::TData(int number, int moduleNumber, string data)
{
	this->number = number;
	this->moduleNumber = moduleNumber;
	this->data = data;
}

int TData::getNumber()
{
	return this->number;
}

int TData::getModuleNumber()
{
	return this->moduleNumber;
}

string TData::getData()
{
	return this->data;
}
