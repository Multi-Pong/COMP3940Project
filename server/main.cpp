//#undef UNICODE
//
//#define WIN32_LEAN_AND_MEAN
//
//#include <winsock2.h>
//#include <windows.h>
//#include <ws2tcpip.h>
//#include <cstdlib>
//#include <cstdio>
//#include <iostream>
//
//#include "../game/GameInstanceSingleton.hpp"
//#include "../sockets/ServerSocket.hpp"
//#include "../threads/SocketThread.hpp"
//
//// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")
//// #pragma comment (lib, "Mswsock.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT 8888

#include "raylib.h"
#include "../threads/ListenThread.hpp"
#include "../game/GameInstanceSingleton.hpp"

int __cdecl main(void) {
    // https://stackoverflow.com/questions/4991967/how-does-wsastartup-function-initiates-use-of-the-winsock-dll
    // In the WSADATA that it populates, it will tell you what version it is offering you based on your request.
    // It also fills in some other information which you are not required to look at if you aren't interested.
    // You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.
//    WSADATA wsaData;
//    int iResult;
//    bool isShutDown = false;
//
//    ServerSocket *ListenSocket;
//    Socket *ClientSocket;
//
//    // Initialize Winsock
//    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//    if (iResult != 0) {
//        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
//    }
//    GameInstanceSingleton::getGameInstance();
//    // Create a SOCKET for the server to listen for client connections.
//    ListenSocket = new ServerSocket(DEFAULT_PORT);
//    while (!isShutDown) {
//        cout << "waiting" << endl;
//        ClientSocket = ListenSocket->Accept();
//        if (ClientSocket != nullptr) {
//            SocketThread *thread = new SocketThread(ClientSocket);
//            thread->start();
//        }
////      shutDownServer();
//    }

    // No longer need server socket
//    closesocket(ListenSocket);
//    ListenSocket->close();
//
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
//
//     cleanup
//    closesocket(ClientSocket);
//    ClientSocket->close();
//    WSACleanup();

    GameInstanceSingleton::getGameInstance();
    ListenThread listenThread;
    listenThread.run();

    InitWindow(FieldSizeWidth, FieldSizeHeight, "Client");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        update(GetTime(), GetFrameTime());


        cout << "DRAWING" << endl;
        BeginDrawing();
        ClearBackground(BLACK);


        for (pair<const int, Player> x: GameInstanceSingleton::getGameInstance().getPlayerList()) {
//                cout << x.second.getID() << endl;
            DrawRectangle((int) x.second.getX(), (int) x.second.getY(), PlayerSize, PlayerSize, WHITE);
        }
        //TODO Draw Ball
        //TODO Draw Score

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    disconnect();
    sleep(3); // ENSURE PROPER SHUTDOWN OF THREADS
    return 0;
    return 0;
}