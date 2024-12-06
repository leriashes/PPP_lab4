#pragma once
#include "TReliableChannel.h"
#define BUFFER_SIZE 10

extern CONDITION_VARIABLE BufferNotEmpty;
extern CONDITION_VARIABLE BufferNotFull; 
extern CRITICAL_SECTION BufferLock;
extern BOOL StopRequested;

class CVChannel
{
private:
	TData Buffer[BUFFER_SIZE];
	ULONG QueueSize;
	ULONG QueueStartOffset;
	ULONG TotalItemsProduced;
	ULONG TotalItemsConsumed;

public:
	int put(TData t);
	int get(TData* resultData);

	CVChannel();
};

