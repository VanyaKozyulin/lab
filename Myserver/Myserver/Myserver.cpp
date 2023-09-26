#include <iostream>
#include <winsock2.h>
#include <clocale>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define BUFLEN 2048
#define PORT 5155

using namespace std;

struct Command {
    string base;
    vector<string> params;
};


void SendMessageToClient(SOCKET socket, const string& message, sockaddr_in& clientAddr) {
    sendto(socket, message.c_str(), message.length(), 0, (sockaddr*)&clientAddr, sizeof(clientAddr));
}

Command ParseCommand(const string& command_string) {
    Command command;
    istringstream commandStream(command_string);

    commandStream >> command.base;

    string param;
    while (commandStream >> param) {
        command.params.push_back(param);
    }

    return command;
}

void ClearDisplay() {
 
    cout << "Выполнена команда: clear display" << endl;
}
void DrawPixel(int x, int y, const string& color) {
    cout << "Выполнена команда: draw pixel, параметры: x = " << x << ", y = " << y << ", color = " << color << endl;
}

void DrawLine(int x1, int y1, int x2, int y2, const string& color) {
    cout << "Выполнена команда: draw line, параметры: x1 = " << x1 << ", y1 = " << y1 << ", x2 = " << x2 << ", y2 = " << y2 << ", color = " << color << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        exit(0);
    }

    SOCKET serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        exit(EXIT_FAILURE);
    }

    cout << "Сервер запущен. Ожидание подключений..." << endl;

    while (true) {
        char buffer[BUFLEN] = {};

        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);

        int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);

        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Ошибка приема данных от клиента" << endl;
            continue;
        }

        string clientIP = inet_ntoa(clientAddr.sin_addr);
        cout << "Подключился клиент " << clientIP << endl;

        string receivedCommand(buffer, bytesReceived);

        if (receivedCommand == "help") {
            string commandList = "Список команд:\n1. clear display\n2. draw pixel\n3. draw line\n4. draw rectangle \n5. fill rectangle \n6. draw ellipse \n7. fill ellipse";
            SendMessageToClient(serverSocket, commandList, clientAddr);
        }
        else if (receivedCommand == "1") {
        }

        else if (receivedCommand == "2") {
            int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Ошибка приема данных от клиента" << endl;
                continue;
            }
            string parameters(buffer, bytesReceived);
            cout << "Получена команда: draw pixel, параметры: " << parameters << endl;
        }
        else if (receivedCommand == "3") {
            int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Ошибка приема данных от клиента" << endl;
                continue;
            }
            string parameters(buffer, bytesReceived);
            cout << "Получена команда: draw line, параметры: " << parameters << endl;
        }
        else if (receivedCommand == "4") {
            int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Ошибка приема данных от клиента" << endl;
                continue;
            }
            string parameters(buffer, bytesReceived);
            cout << "Получена команда: draw rectangle, параметры: " << parameters << endl;
        }
        else if (receivedCommand == "5") {
            int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Ошибка приема данных от клиента" << endl;
                continue;
            }
            string parameters(buffer, bytesReceived);
            cout << "Получена команда: fill rectangle, параметры: " << parameters << endl;
        }
        else if (receivedCommand == "6") {
            int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Ошибка приема данных от клиента" << endl;
                continue;
            }
            string parameters(buffer, bytesReceived);
            cout << "Получена команда: draw ellipse, параметры: " << parameters << endl;
        }
        else if (receivedCommand == "7") {
            int bytesReceived = recvfrom(serverSocket, buffer, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrSize);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Ошибка приема данных от клиента" << endl;
                continue;
            }
            string parameters(buffer, bytesReceived);

            cout << "Получена команда: fill ellipse, параметры: " << parameters << endl;
        }

        else {
            cout << "Неизвестная команда: " << receivedCommand << endl;
        }

    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
