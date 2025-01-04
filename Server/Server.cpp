#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <thread>

#pragma comment(lib, "ws2_32.lib") // Подключение библиотеки WinSock

using namespace std;

struct Channel
{
    bool reliable;
    queue<vector<char>> data;
    queue<SOCKET> waitingClients;
};

int main() {
    setlocale(LC_ALL, "rus");

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Ошибка инициализации WinSock. Код ошибки: " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }

    unordered_map<SOCKET, pair<string, uint16_t>> clientsInfo; // Информация о клиентах
    SOCKET listener; // Слушающий сокет
    set<SOCKET> clients; // Набор клиентских сокетов
    vector<char> buffer(1024); // Буфер для данных
    fd_set readset; // Набор сокетов для select
    unordered_map<string, Channel> channelSockets;

    // Создание сокета
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener == INVALID_SOCKET) {
        cerr << "Невозможно создать сокет. Код ошибки: " << WSAGetLastError() << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Установка сокета в неблокирующий режим
    u_long mode = 1;
    if (ioctlsocket(listener, FIONBIO, &mode) != 0) {
        cerr << "Ошибка установки неблокирующего режима. Код ошибки: " << WSAGetLastError() << endl;
        closesocket(listener);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    sockaddr_in sockaddrIn{};
    sockaddrIn.sin_family = AF_INET;
    sockaddrIn.sin_port = htons(8484);
    sockaddrIn.sin_addr.s_addr = INADDR_ANY;

    // Разрешение повторного использования адреса
    int flag = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(int)) == SOCKET_ERROR) {
        cerr << "Ошибка установки SO_REUSEADDR. Код ошибки: " << WSAGetLastError() << endl;
        closesocket(listener);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Привязка сокета
    if (bind(listener, (struct sockaddr*)&sockaddrIn, sizeof(sockaddrIn)) == SOCKET_ERROR) {
        cerr << "Ошибка bind. Код ошибки: " << WSAGetLastError() << endl;
        closesocket(listener);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Слушаем подключения
    if (listen(listener, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Ошибка listen. Код ошибки: " << WSAGetLastError() << endl;
        closesocket(listener);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    cout << "Сервер запущен на порту 8484" << endl;

    while (true) {
        FD_ZERO(&readset);
        FD_SET(listener, &readset); // Добавляем слушающий сокет

        for (auto client : clients) {
            FD_SET(client, &readset); // Добавляем клиентские сокеты
        }

        timeval timeout;
        timeout.tv_sec = 2 * 60;
        timeout.tv_usec = 0;

        int maxSock = listener;
        if (!clients.empty()) {
            maxSock = max(listener, *max_element(clients.begin(), clients.end()));
        }

        // Используем select для мультиплексирования
        int activity = select(maxSock + 1, &readset, nullptr, nullptr, &timeout);
        if (activity < 0) {
            cerr << "Ошибка select. Код ошибки: " << WSAGetLastError() << endl;
            closesocket(listener);
            WSACleanup();
            exit(EXIT_FAILURE);
        }

        // Проверяем слушающий сокет
        if (FD_ISSET(listener, &readset)) {
            sockaddr_in clientInfo;
            int len = sizeof(clientInfo);
            SOCKET clientSock = accept(listener, (sockaddr*)&clientInfo, &len);
            if (clientSock == INVALID_SOCKET) {
                cerr << "Ошибка accept. Код ошибки: " << WSAGetLastError() << endl;
                continue;
            }

            // Буфер для IP-адреса клиента
            char ipStr[INET_ADDRSTRLEN]; // Для IPv4 (для IPv6 можно использовать INET6_ADDRSTRLEN)
            inet_ntop(AF_INET, &(clientInfo.sin_addr), ipStr, INET_ADDRSTRLEN); // Преобразуем IP в строку
            string clientIP = ipStr; // Преобразуем в std::string
            uint16_t clientPort = ntohs(clientInfo.sin_port);

            cout << "Подключился клиент " << clientIP << ":" << clientPort << endl;

            // Сохраняем информацию о клиенте
            clientsInfo[clientSock] = { clientIP, clientPort };
            clients.insert(clientSock);
        }

        // Проверяем активность клиентов
        for (auto it = clients.begin(); it != clients.end();) {
            SOCKET clientSock = *it;
            if (FD_ISSET(clientSock, &readset)) {
                int bytesRead = recv(clientSock, buffer.data(), 40, 0);
                if (bytesRead <= 0) {
                    // Обрыв связи
                    cout << "Произошел обрыв связи с " << clientsInfo[clientSock].first
                        << ":" << clientsInfo[clientSock].second << endl;

                    closesocket(clientSock);
                    clientsInfo.erase(clientSock);
                    it = clients.erase(it);
                }
                else {
                    // Обработка данных
                    cout << "От клиента " << clientsInfo[clientSock].first << ":"
                        << clientsInfo[clientSock].second << " получено " << bytesRead
                        << " байт:  " << buffer.data() << endl;

                    string message = buffer.data();

                    size_t pos = message.find(' ');

                    if (pos != string::npos) {
                        string command = message.substr(0, pos);

                        if (command == "REGISTER")
                        {
                            string params = message.substr(pos + 1);

                            pos = params.find(' ');

                            if (pos != string::npos) {

                                string channel = params.substr(0, pos);

                                if (channelSockets.find(channel) == channelSockets.end()) {

                                    string type = params.substr(pos + 1);

                                    channelSockets[channel].reliable = (type == "1");

                                    cout << "Регистрация канала " << channel << endl << endl;
                                }
                            }
                        }
                        else if (command == "PUT")
                        {
                            string params = message.substr(pos + 1);

                            size_t pos2 = params.find(' ');

                            if (pos2 != string::npos) {

                                string channel = params.substr(0, pos2);

                                if (channelSockets.find(channel) != channelSockets.end()) {

                                    vector<char> data(buffer.begin() + pos + pos2 + 2, buffer.begin() + pos + pos2 + 10);

                                    if (channelSockets[channel].reliable)
                                    {
                                        channelSockets[channel].data.push(data);
                                    }
                                    else
                                    {
                                        if (!channelSockets[channel].data.empty())
                                            channelSockets[channel].data.pop();
                                        channelSockets[channel].data.push(data);
                                    }

                                    cout << "Получены данные для отправки в канал " << channel << endl << endl;

                                    if (channelSockets[channel].waitingClients.size() > 0)
                                    {
                                        vector<char> data = channelSockets[channel].data.front();
                                        channelSockets[channel].data.pop();

                                        int sendResult = send(channelSockets[channel].waitingClients.front(), data.data(), data.size(), 0);

                                        channelSockets[channel].waitingClients.pop();

                                        if (sendResult == SOCKET_ERROR) {
                                            cerr << "Ошибка отправки сообщения. Код: " << WSAGetLastError() << endl << endl;
                                        }
                                        else {
                                            cout << "Сообщение отправлено клиенту: " << data.data() << endl << endl;
                                        }
                                    }
                                }
                            }
                        }
                        else if (command == "GET")
                        {
                            string channel = message.substr(pos + 1);

                            if (channelSockets.find(channel) != channelSockets.end()) {

                                if (channelSockets[channel].data.size() > 0)
                                {
                                    vector<char> data = channelSockets[channel].data.front();
                                    channelSockets[channel].data.pop();

                                    int sendResult = send(clientSock, data.data(), data.size(), 0);

                                    if (sendResult == SOCKET_ERROR) {
                                        cerr << "Ошибка отправки сообщения. Код: " << WSAGetLastError() << endl << endl;
                                    }
                                    else {
                                        cout << "Сообщение отправлено клиенту: " << data.data() << endl << endl;
                                    }
                                }
                                else 
                                {
                                    channelSockets[channel].waitingClients.push(clientSock);
                                }
                            }
                        }
                        else if (command == "UNREGISTER")
                        {

                        }
                    }

                    fill(buffer.begin(), buffer.end(), 0);

                    ++it;
                }
            }
            else {
                ++it;
            }
        }

        this_thread::yield(); // Освобождаем поток
    }

    // Завершаем работу
    closesocket(listener);
    WSACleanup();
    return 0;
}
