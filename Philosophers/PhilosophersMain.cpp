#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "..\TReliableChannel.h"
using namespace std;

#define PRODUCER_SLEEP_TIME_MS 50
#define SLEEP_TIME_MS 20

TReliableChannel* chan[5];    // индивидуальные каналы сервисных процессов

TSemaphore pr = TSemaphore("CriticalSection", 1);

void createChan(int n) {
    char name[100] = "A_channel_";
    for (int i = 0; i < n; i++) {
        chan[i] = new TReliableChannel(name, 1024);
        name[0]++;
    }
}

void deleteChan(int n) {
    for (int i = 0; i < n; i++) {
        delete chan[i];
    }
}


void  servFun(int i, int n, TSemaphore freeSem) {
    int sl = (i - 1 + n) % n, sr = (i + 1) % n;
    bool  free = true;
    bool  freeLeft = false;
    bool  myProc = false, right = false;

    while (true) {     // цикл  обслуживания
        TData  data;
        chan[i]->get(&data);

        switch (data.getNumber()) {

            // (1) реакция  на  запрос   ресурса   справа
        case  FROM_RIGHT:
            pr.P();  
            cout << i << "  servFun  FROM_RIGHT  " << i << endl;
            pr.V();

            if (free && ((myProc == false) || (i % 2 == 0))) { // не жадный
                chan[sr]->put(TData(OK, 0));
                free = false;
            }
            else 
                right = true;

            break;

            //  (2) обслуживание  собственного   процесса
            // получен  запрос
        case   NEED_FORKS:
            pr.P();  
            cout << i << " servFun   NEED_FORKS  " << i << endl; 
            pr.V();

            myProc = true;
            chan[sr]->put(TData(FROM_RIGHT, 0));
            break;

            //  (3) обслуживание  собственного   процесса
            // после   запроса (2)  получен ресурс  слева
        case  OK:
            pr.P();  
            cout << "  servFun   OK  " << i << endl;  
            pr.V();

            freeLeft = true;
            if (myProc && free && freeLeft) {
                freeSem.V();
                free = myProc = false;
            }

            break;

            //  (4) возврат   ресурса  от   правого   сервиса
        case  RET_RIGHT:
            pr.P();  
            cout << "  servFun  RET_RIGHT  " << i << endl; 
            pr.V();

            free = true;
            if (myProc && freeLeft && free) {
                freeSem.V();
                free = myProc = false;
            }

            break;

            //  (5) возврат  ресурсов  от  управляемого  процесса
        case    FREE_FORKS:
            pr.P();  
            cout << i << "  servFun  FREE_FORKS  " << i << endl;  
            pr.V();

            free = true;
            myProc = freeLeft = false;

            chan[sl]->put(TData(RET_RIGHT, 0));
            if (right == true) {
                chan[sr]->put(TData(OK, 0));
                free = false;
            }

            break;

        }
    }
}


DWORD WINAPI ServThreadProc(PVOID p) {
    ULONG ServId = (ULONG)(ULONG_PTR)p;
    int index = ServId;
    char nameSem[100] = "nameOfSemFree_";
    int k = strlen(nameSem);
    nameSem[k] = '0' + index; nameSem[k + 1] = 0;
    TSemaphore free = TSemaphore(nameSem, false);

    pr.P(); 
    cout << "servProc started " << ServId << endl; 
    pr.V();

    servFun(index, 5, free);

    pr.P();  
    cout << "servProc stoped  " << ServId << endl; 
    pr.V();

    return 0;
}

DWORD WINAPI PhilosopherThread(PVOID p) {
    ULONG PhilosopherId = (ULONG)(ULONG_PTR)p;
    int index = PhilosopherId;
    char nameSem[100] = "nameOfSemFree_";
    int k = strlen(nameSem);
    nameSem[k] = '0' + index; 
    nameSem[k + 1] = 0;
    TSemaphore free = TSemaphore(nameSem, false);

    pr.P(); 
    cout << "Philosopher  started " << PhilosopherId << endl; 
    pr.V();

    int i = 0;

    while (i < 1) {

        pr.P();
        cout << "   thinking  " << index << endl;
        pr.V();

        Sleep(SLEEP_TIME_MS);

        pr.P();
        cout << "  NEED_FORKS   " << index << endl;
        pr.V();

        chan[index]->put(TData(NEED_FORKS, 0));

        free.P();

        pr.P();  
        cout << "   eating  " << index << endl; 
        pr.V();

        Sleep(SLEEP_TIME_MS);

        chan[index]->put(TData(FREE_FORKS, 0));

        pr.P();  
        cout << "   FREE_FORKS  " << index << endl;  
        pr.V();

        i++;
    }

    pr.P();  
    cout << "Philosopher  stoped   " << PhilosopherId << endl; 
    pr.V();

    return 0;
}

int main() {

    int n = 5;
    DWORD id;
    HANDLE serv[10], phil[10];
    createChan(n);

    for (int i = 0; i < n; i++) {
        serv[i] = CreateThread(NULL, 0, ServThreadProc, (PVOID)i, 0, &id);
        phil[i] = CreateThread(NULL, 0, PhilosopherThread, (PVOID)i, 0, &id);
    }

    for (int i = 0; i < 5; i++)
        WaitForSingleObject(serv[i], INFINITE);
    for (int i = 0; i < 5; i++)
        WaitForSingleObject(phil[i], INFINITE);

    deleteChan(n);

    return 0;
}
