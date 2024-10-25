#pragma once
#include "TChannel.h"
class TReliableChannel : public TChannel
{
private:
	TSemaphore* free;

public:
	void put(TData t) override;
	void get(TData* resultData) override;

	TReliableChannel();
	~TReliableChannel();
};

