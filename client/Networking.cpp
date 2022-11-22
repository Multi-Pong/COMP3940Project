//
// Created by Admin on 2022-11-14.
//
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdio>
#include "Networking.hpp"
#include "packets/ClientPacketBuilder.hpp"
#include "packets/ClientPacketReader.hpp"
#include "../threads/ClientReaderThread.hpp"
#include "../game/GameInstanceSingleton.hpp"

Socket *sock = nullptr;
SOCKET ConnectSocket = INVALID_SOCKET;
ClientReaderThread *thread = nullptr;
int *threadRunning = new int;
double inputUpdateInterval = 1.0f / 20.0f;
double lastNow = 0;
//int n = 1;

void connect() {
    // https://stackoverflow.com/questions/4991967/how-does-wsastartup-function-initiates-use-of-the-winsock-dll
    // In the WSADATA that it populates, it will tell you what version it is offering you based on your request.
    // It also fills in some other information which you are not required to look at if you aren't interested.
    // You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.
    WSADATA wsaData;
    struct addrinfo *result = nullptr,
            *ptr = nullptr,
            hints{};
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints)); // Set bits to 0
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_IP, to_string(DEFAULT_PORT).c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);


    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }

    sock = new Socket(ConnectSocket);
    // Receive until the peer closes the connection
    // Put reader into thread or something
    cout << "Create thread" << endl;
    delete thread;
    thread = new ClientReaderThread(&sock, threadRunning);
    thread->start();
    string packet = ClientPacketBuilder::buildPacket(*GameInstanceSingleton::getGameInstance().getLocalPlayer());
    sock->sendResponse(packet);
}

void update(double now, float deltaT) {
    // Send an initial buffer
    if (now - lastNow > inputUpdateInterval && (GameInstanceSingleton::getGameInstance().localHasMoved())) { // send based on inputUpdateInterval
        cout << "SENDING" << endl;
        string packet = ClientPacketBuilder::buildPacket(*GameInstanceSingleton::getGameInstance().getLocalPlayer());
//        n += 1;
//        cout << "PACKET:" << endl;
//        cout << packet << endl;
        sock->sendResponse(packet);
        lastNow = now;
    }
}

bool isConnected() {
    //This might be wrong
//    cout << sock << endl;
    if (sock != nullptr && sock->isConnected()) {
        return true;
    }
    delete sock;
    sock = nullptr;
    return false;
}

void disconnect() {
    if (sock != nullptr) {
        sock->shutDown();
        sock->close();
    }
    WSACleanup();
}
