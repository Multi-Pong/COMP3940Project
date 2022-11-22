//
// Created by Admin on 2022-11-21.
//
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "../game/GameInstanceSingleton.hpp"
#include "../sockets/ServerSocket.hpp"
#include "../threads/SocketThread.hpp"

#include "ListenThread.hpp"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 8888

ListenThread::ListenThread(): Thread(this) {

}

void ListenThread::run() {
// https://stackoverflow.com/questions/4991967/how-does-wsastartup-function-initiates-use-of-the-winsock-dll
    // In the WSADATA that it populates, it will tell you what version it is offering you based on your request.
    // It also fills in some other information which you are not required to look at if you aren't interested.
    // You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.
    WSADATA wsaData;
    int iResult;

    Socket *ClientSocket;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }
    GameInstanceSingleton::getGameInstance();
    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = new ServerSocket(DEFAULT_PORT);
    while (WSAGetLastError() == 0) {
        cout << "waiting" << endl;
        ClientSocket = ListenSocket->Accept();
        if (ClientSocket != nullptr) {
            SocketThread *thread = new SocketThread(ClientSocket);
            thread->start();
        }
    }
}

void ListenThread::send(std::string) {
// DO NOTHING
}

ListenThread::~ListenThread() {
    ListenSocket->close();
    delete ListenSocket;
    WSACleanup();
}
