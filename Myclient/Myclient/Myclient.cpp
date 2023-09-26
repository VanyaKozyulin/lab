#include <iostream>
#include <winsock2.h>
#include <clocale>
#include <string>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define SERVER_IP "127.0.0.1"
#define PORT 5155

using namespace std;

void SendCommandToServer(SOCKET socket, const string& command, sockaddr_in& serverAddr) {
    sendto(socket, command.c_str(), command.length(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
}

string ReceiveResponseFromServer(SOCKET socket, sockaddr_in& serverAddr) {
    char buffer[2048];
    int serverAddrSize = sizeof(serverAddr);
    int bytesReceived = recvfrom(socket, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddr, &serverAddrSize);

    if (bytesReceived == SOCKET_ERROR) {
        cerr << "Ошибка приема ответа от сервера" << endl;
        return "";
    }

    buffer[bytesReceived] = '\0';
    return buffer;
}

int main() {
    setlocale(LC_ALL, "ru");

    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        exit(0);
    }

    SOCKET clientSocket;
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while (true) {
        cout << "Выберите команду (или введите 'exit' для выхода, 'help' для получения списка команд):" << endl;
        cout << "1. clear display" << endl;
        cout << "2. draw pixel" << endl;
        cout << "3. draw line" << endl;
        cout << "4. draw rectangle" << endl;
        cout << "5. fill rectangle" << endl;
        cout << "6. draw ellipse" << endl;
        cout << "7. fill ellipse" << endl;
        cout << "0. Введите 'exit' для выхода" << endl;
        cout << "> ";

        string choice;
        getline(cin, choice);

        if (choice == "exit") {
            break;
        }
        else if (choice == "help") {
            SendCommandToServer(clientSocket, choice, serverAddr);
            string response = ReceiveResponseFromServer(clientSocket, serverAddr);
            cout << "Список команд от сервера:" << endl;
            cout << response << endl;
        }
        else if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7") {
            SendCommandToServer(clientSocket, choice, serverAddr);

         
            string parameters;
            if (choice == "2") {

                string x, y, color;
                cout << "Введите x0: ";
                getline(cin, x);
                cout << "Введите y0: ";
                getline(cin, y);
                cout << "Введите color (например, FF0000): ";
                getline(cin, color);

                string parameters = x + " " + y + " " + color;
                SendCommandToServer(clientSocket, parameters, serverAddr);
            }
  
            if (choice == "3") {
                string x, y, x1, y1, color;
                cout << "Введите x0: ";
                getline(cin, x);
                cout << "Введите y0: ";
                getline(cin, y);

                cout << "Введите x1: ";
                getline(cin, x1);
                cout << "Введите y1: ";
                getline(cin, y1);
                cout << "Введите color (например, FF0000): ";
                getline(cin, color);

                string parameters = x + " " + y + " " + x1 + " " + y1 + " " + color; 
                SendCommandToServer(clientSocket, parameters, serverAddr);

            }

            if (choice == "4") {
                string x, y, w, h, color;
                cout << "Введите x0: ";
                getline(cin, x);
                cout << "Введите y0: ";
                getline(cin, y);
                cout << "Введите w: ";
                getline(cin, w);
                cout << "Введите h: ";
                getline(cin, h);
                cout << "Введите color (например, FF0000): ";
                getline(cin, color);

                string parameters = x + " " + y + " " + w + " " + h + " " + color; 
                SendCommandToServer(clientSocket, parameters, serverAddr);

            }
            if (choice == "5") {
                string x, y, w, h, color;
                cout << "Введите x0: ";
                getline(cin, x);
                cout << "Введите y0: ";
                getline(cin, y);
                cout << "Введите w: ";
                getline(cin, w);
                cout << "Введите h: ";
                getline(cin, h);
                cout << "Введите color (например, FF0000): ";
                getline(cin, color);

                string parameters = x + " " + y + " " + w + " " + h + " " + color;
                SendCommandToServer(clientSocket, parameters, serverAddr);

            }
            if (choice == "6") {
                string x, y, rx, ry, color;
                cout << "Введите x0: ";
                getline(cin, x);
                cout << "Введите y0: ";
                getline(cin, y);
                cout << "Введите radius x: ";
                getline(cin, rx);
                cout << "Введите radius y: ";
                getline(cin, ry);
                cout << "Введите color (например, FF0000): ";
                getline(cin, color);

                string parameters = x + " " + y + " " + rx + " " + ry + " " + color;
                SendCommandToServer(clientSocket, parameters, serverAddr);

            }
            if (choice == "7") {
                string x, y, rx, ry, color;
                cout << "Введите x0: ";
                getline(cin, x);
                cout << "Введите y0: ";
                getline(cin, y);
                cout << "Введите radius x: ";
                getline(cin, rx);
                cout << "Введите radius y: ";
                getline(cin, ry);
                cout << "Введите color (например, FF0000): ";
                getline(cin, color);

                string parameters = x + " " + y + " " + rx + " " + ry + " " + color;
                SendCommandToServer(clientSocket, parameters, serverAddr);

            }



            string response = ReceiveResponseFromServer(clientSocket, serverAddr);
            cout << "Ответ от сервера:" << endl;
            cout << response << endl;
        }
        else {
            cout << "Неверный выбор команды. Попробуйте еще раз." << endl;
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
