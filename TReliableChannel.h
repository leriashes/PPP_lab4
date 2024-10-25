#pragma once
#include "TChannel.h"
class TReliableChannel : public TChannel
{
private:
	TSemaphore* free;

public:
	void put(TData t) override;
	void get(TData* resultData) override;

	TReliableChannel(const char* name, size_t size);
	~TReliableChannel();
};

