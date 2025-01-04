#include "NetworkChannel.h"

void NetworkChannel::put(TData t)
{
    vector<char> buffer(sizeof(TData));

    memcpy(buffer.data(), &t, sizeof(TData));

    vector<char> data;

    string header = "PUT ";

    data.insert(data.end(), header.begin(), header.end());
    data.insert(data.end(), name.begin(), name.end());
    data.insert(data.end(), ' ');
    data.insert(data.end(), buffer.begin(), buffer.end());

    //string data = "PUT " + this->name + " " + to_string(t.getModuleNumber()) + " " + to_string(t.getNumber());

    int bytesSent = send(channelSocket, data.data(), data.size(), 0);
    if (bytesSent == SOCKET_ERROR) {
        cerr << "Ошибка отправки данных: " << WSAGetLastError() << endl;
    }

    cout << "\nNET >> данные отправлены:  " << string(buffer.data());
}

void NetworkChannel::get(TData* resultData)
{
    vector<char> buffer(sizeof(TData));

    string data = "GET " + this->name;

    int bytesSent = send(channelSocket, data.c_str(), data.size(), 0);
    if (bytesSent == SOCKET_ERROR) {
        cerr << "Ошибка отправки данных: " << WSAGetLastError() << endl;
    }

    int bytesReceived = recv(channelSocket, buffer.data(), buffer.size(), 0);
    if (bytesReceived == SOCKET_ERROR) {
        cerr << "Ошибка получения данных: " << WSAGetLastError() << endl;
    }

    memcpy(resultData, buffer.data(), sizeof(TData));

    cout << "\nNET >> данные получены:  " << buffer.data();
}

NetworkChannel::NetworkChannel(string name, string serverAddress, uint16_t port) : NetworkChannel(name, serverAddress, port, true)
{
}

NetworkChannel::NetworkChannel(string name, string serverAddress, uint16_t port, bool reliable)
{
    this->name = name;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Ошибка инициализации WinSock. Код ошибки: " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

    channelSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (channelSocket == INVALID_SOCKET) {
        throw runtime_error("Ошибка создания сокета для канала");
    }

    if (connect(channelSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(channelSocket);
        throw runtime_error("Ошибка подключения к серверу канала");
    }

    this->reliable = reliable;

    if (reliable) {
        send(channelSocket, ("REGISTER " + name + " 1").c_str(), sizeof(name), 0);
    }
    else {
        send(channelSocket, ("REGISTER " + name + " 0").c_str(), sizeof(name), 0);
    }
}

NetworkChannel::~NetworkChannel()
{
    if (channelSocket != INVALID_SOCKET) {
        closesocket(channelSocket);
    }
}
