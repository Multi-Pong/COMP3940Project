#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "sockets/ServerSocket.hpp"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(void) {
    // https://stackoverflow.com/questions/4991967/how-does-wsastartup-function-initiates-use-of-the-winsock-dll
    // In the WSADATA that it populates, it will tell you what version it is offering you based on your request.
    // It also fills in some other information which you are not required to look at if you aren't interested.
    // You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.
    WSADATA wsaData;
    int iResult;

    ServerSocket *ListenSocket;
    Socket *ClientSocket;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

//    ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_INET;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
//    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//    if (iResult != 0) {
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        return 1;
//    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = new ServerSocket(8888);
    while (true) {
        cout << "waiting" << endl;
        ClientSocket = ListenSocket->Accept();
//        Router *thread = new Router(cs);
//        thread->start();
    }
//    socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//    if (ListenSocket == INVALID_SOCKET) {
//        printf("socket failed with error: %ld\n", WSAGetLastError());
//        freeaddrinfo(result);
//        WSACleanup();
//        return 1;
//    }

    // Setup the TCP listening socket
//    iResult = bind(ListenSocket, result->ai_addr, (int) result->ai_addrlen);
//    if (iResult == SOCKET_ERROR) {
//        printf("bind failed with error: %d\n", WSAGetLastError());
//        freeaddrinfo(result);
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }

//    freeaddrinfo(result);

//    iResult = listen(ListenSocket, SOMAXCONN);
//    if ((iResult = listen(ListenSocket, SOMAXCONN)) == SOCKET_ERROR) {
//        printf("listen failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }

//    // Accept a client socket
//    ClientSocket = accept(ListenSocket, NULL, NULL);
//    if (ClientSocket == INVALID_SOCKET) {
//        printf("accept failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return 1;
//    }

    // No longer need server socket
//    closesocket(ListenSocket);
    ListenSocket->close();

    // Receive until the peer shuts down the connection
    do {

//        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
//            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
//                closesocket(ClientSocket);
                ClientSocket->close();
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        } else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
//            closesocket(ClientSocket);
            ClientSocket->close();
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = ClientSocket->shutDown();
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
//        closesocket(ClientSocket);
        ClientSocket->close();
        WSACleanup();
        return 1;
    }

    // cleanup
//    closesocket(ClientSocket);
    ClientSocket->close();
    WSACleanup();

    return 0;
}