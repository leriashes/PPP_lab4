#pragma once
#include "TChannel.h"
class TReliableChannel : public TChannel
{
private:
	TSemaphore* free;

public:
	void put(TData t);
	void get(TData* resultData);

	TReliableChannel();
	~TReliableChannel();
};

