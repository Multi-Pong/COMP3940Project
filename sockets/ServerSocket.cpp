//
// Created by Admin on 2022-11-10.
//

#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port) {
    int iResult;

    struct addrinfo *result = NULL;
    struct addrinfo hints{};
    ZeroMemory(&hints, sizeof(hints)); // Set bits to 0
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if ((iResult = getaddrinfo(NULL, to_string(port).c_str(), &hints, &result)) != 0) {
        perror(("getaddrinfo failed with error: " + to_string(iResult) + "\n").c_str());
        WSACleanup();
        return;
    }

    // Create a SOCKET for the server to listen for client connections.
    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock == INVALID_SOCKET) {
        perror(("socket failed with error: " + to_string(WSAGetLastError()) + "\n").c_str());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Set up the TCP listening socket
    if ((iResult = bind(sock, result->ai_addr, (int) result->ai_addrlen)) == SOCKET_ERROR) {
        perror(("bind failed with error: " + to_string(WSAGetLastError()) + "\n").c_str());
        freeaddrinfo(result);
        closesocket(sock);
        WSACleanup();
        return;
    }


    freeaddrinfo(result);
    if ((iResult = listen(sock, SOMAXCONN)) == SOCKET_ERROR) {
        perror(("listen failed with error: " + to_string(WSAGetLastError()) + "\n").c_str());
        closesocket(sock);
        WSACleanup();
        return;
    }
}

Socket *ServerSocket::Accept() {
// Accept a client socket
    SOCKET cSock = accept(sock, NULL, NULL);
    if (cSock == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(cSock);
        WSACleanup();
        return nullptr;
    }
    Socket *cs = new Socket(cSock);
    return cs;
}

ServerSocket::~ServerSocket() {}