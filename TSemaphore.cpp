#include "TSemaphore.h"

void TSemaphore::P()
{ 
	while (!count);    
	count = 0;
}

void TSemaphore::V()
{
	count = 1;
}

TSemaphore::TSemaphore(int start)
{
	if (start) 
		count = 1;
	else 
		count = 0;
}

TSemaphore::~TSemaphore()
{
}
