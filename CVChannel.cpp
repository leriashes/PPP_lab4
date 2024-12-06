#include "CVChannel.h"

BOOL StopRequested = FALSE;
CONDITION_VARIABLE BufferNotEmpty;
CONDITION_VARIABLE BufferNotFull;
CRITICAL_SECTION BufferLock;

int CVChannel::put(TData t)
{
    EnterCriticalSection(&BufferLock);

    while (QueueSize == BUFFER_SIZE && StopRequested == FALSE) {
        SleepConditionVariableCS(&BufferNotFull, &BufferLock, INFINITE);
    }

    if (StopRequested == TRUE) {
        LeaveCriticalSection(&BufferLock);
        return 1;
    }

    Buffer[(QueueStartOffset + QueueSize) % BUFFER_SIZE] = t;

    QueueSize++;
    TotalItemsProduced++;

    cout << "\n+++ ÎÒÏÐÀÂËÅÍÀ ÏÎÐÖÈß ÄÀÍÍÛÕ #" << TotalItemsProduced << "    Ðàçìåð î÷åðåäè: " << QueueSize;

    LeaveCriticalSection(&BufferLock);

    WakeConditionVariable(&BufferNotEmpty);

    return 0;
}

int CVChannel::get(TData* resultData)
{
    EnterCriticalSection(&BufferLock);

    while (QueueSize == 0 && StopRequested == FALSE) {
        SleepConditionVariableCS(&BufferNotEmpty, &BufferLock, INFINITE);
    }

    if (StopRequested == TRUE && QueueSize == 0) {
        LeaveCriticalSection(&BufferLock);
        return 1;
    }

    *resultData = Buffer[QueueStartOffset++];

    if (QueueStartOffset == BUFFER_SIZE) {
        QueueStartOffset = 0;
    }

    QueueSize--;

    TotalItemsConsumed++;

    cout << "\n--- ÏÎËÓ×ÅÍÀ ÏÎÐÖÈß ÄÀÍÍÛÕ #" << TotalItemsConsumed << "    Ðàçìåð î÷åðåäè: " << QueueSize;

    LeaveCriticalSection(&BufferLock);

    WakeConditionVariable(&BufferNotFull);

    return 0;

}

CVChannel::CVChannel()
{
    QueueSize = 0;
    QueueStartOffset = 0;
    TotalItemsProduced = 0;
    TotalItemsConsumed = 0;
}
