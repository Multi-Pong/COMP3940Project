#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "sockets/ServerSocket.hpp"
#include "threads/SocketThread.hpp"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 8888

int __cdecl main(void) {
    // https://stackoverflow.com/questions/4991967/how-does-wsastartup-function-initiates-use-of-the-winsock-dll
    // In the WSADATA that it populates, it will tell you what version it is offering you based on your request.
    // It also fills in some other information which you are not required to look at if you aren't interested.
    // You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.
    WSADATA wsaData;
    int iResult;
    bool isShutDown = false;

    ServerSocket *ListenSocket;
    Socket *ClientSocket;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = new ServerSocket(DEFAULT_PORT);
    while (!isShutDown) {
        cout << "waiting" << endl;
        ClientSocket = ListenSocket->Accept();
        SocketThread *thread = new SocketThread(ClientSocket);
        thread->start();
//      shutDownServer();
    }

    // No longer need server socket
//    closesocket(ListenSocket);
//    ListenSocket->close();

    // TODO Put in game thread
//    // Receive until the peer shuts down the connection
//    int iSendResult;
//    char recvbuf[DEFAULT_BUFLEN];
//    int recvbuflen = DEFAULT_BUFLEN;
//    do {
//
//        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
//        if (iResult > 0) {
//            printf("Bytes received: %d\n", iResult);
//
//            // Echo the buffer back to the sender
//            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
//            if (iSendResult == SOCKET_ERROR) {
//                printf("send failed with error: %d\n", WSAGetLastError());
//                closesocket(ClientSocket);
//                ClientSocket->close();
//                WSACleanup();
//                return 1;
//            }
//            printf("Bytes sent: %d\n", iSendResult);
//        } else if (iResult == 0)
//            printf("Connection closing...\n");
//        else {
//            printf("recv failed with error: %d\n", WSAGetLastError());
//            closesocket(ClientSocket);
//            ClientSocket->close();
//            WSACleanup();
//            return 1;
//        }
//
//    } while (iResult > 0);
//
//    // shutdown the connection since we're done
//    iResult = ClientSocket->shutDown();
//    if (iResult == SOCKET_ERROR) {
//        printf("shutdown failed with error: %d\n", WSAGetLastError());
////        closesocket(ClientSocket);
//        ClientSocket->close();
//        WSACleanup();
//        return 1;
//    }

//     cleanup
//    closesocket(ClientSocket);
    ClientSocket->close();
    WSACleanup();

    return 0;
}