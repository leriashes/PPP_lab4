#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>
#include "TData.h"

#pragma comment(lib, "ws2_32.lib") // Подключение библиотеки WinSock

class NetworkChannel
{
private:
    SOCKET channelSocket;
    string name;
    bool reliable;

public:
    void put(TData t);
    void get(TData* resultData);

    NetworkChannel(string name, string serverAddress, uint16_t port);
    NetworkChannel(string name, string serverAddress, uint16_t port, bool reliable);
    ~NetworkChannel();
};

