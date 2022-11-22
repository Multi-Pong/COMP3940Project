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

#include <unistd.h>
#include "raylib.h"
#include "../threads/ListenThread.hpp"
#include "../game/GameInstanceSingleton.hpp"

void shutdown();

int __cdecl main() {
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
    auto *listenThread = new ListenThread{};
    listenThread->start();

    InitWindow(FieldSizeWidth, FieldSizeHeight, "Server");
    SetTargetFPS(60);
    Ball* startBall = new Ball(FieldSizeWidth/2, FieldSizeHeight/2);
    GameInstanceSingleton::getGameInstance().setBall(startBall);
    while (!WindowShouldClose()) {

        //TODO Implement game logic
//        update(GetTime(), GetFrameTime());


        cout << "DRAWING" << endl;
        BeginDrawing();
        ClearBackground(BLACK);

        vector<Rectangle*> playerHitboxes;
        for (pair<const int, Player> x: GameInstanceSingleton::getGameInstance().getPlayerList()) {
//                cout << x.second.getID() << endl;
            DrawRectangle((int) x.second.getX(), (int) x.second.getY(), PlayerWidth, PlayerHeight, WHITE);
            Rectangle* r = new Rectangle();
            r->x = x.second.getX();
            r->y = x.second.getY();
            r->height = PlayerHeight;
            r->width = PlayerWidth;
            playerHitboxes.push_back(r);
        }

        //TODO Draw Ball
        Ball* b = GameInstanceSingleton::getGameInstance().getBall();
        if (GameInstanceSingleton::getGameInstance().getPlayerList().size() > 1){
            if (b->getXSpeed() == 0 && b->getYSpeed() == 0){
                b->setXSpeed(3);
            }
        }
        DrawCircle(b->getXCoord(), b->getYCoord(), BallRadius, WHITE);
        Rectangle ballHitbox{static_cast<float>(b->getXCoord()), static_cast<float>(b->getYCoord()), BallRadius*2, BallRadius*2};
        for(Rectangle* hb : playerHitboxes){
            if(CheckCollisionRecs(*hb, ballHitbox)){
                b->setXSpeed(b->getXSpeed() * -1.2);
                b->setYSpeed(b->getYSpeed() * -1.2);
            }
        }
        if (b->getYCoord() < BallRadius){
            b->setYCoord(BallRadius);
            b->setYSpeed(b->getYSpeed() * -1);
        }
        if (b->getYCoord() + BallRadius > FieldSizeHeight){
            b->setYCoord(FieldSizeHeight - BallRadius);
            b->setYSpeed(b->getYSpeed() * -1);
        }
        b->setXCoord(b->getXCoord() + b->getXSpeed());
        b->setYCoord(b->getYCoord() + b->getYSpeed());
        //TODO Draw Score

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    shutdown();
    delete listenThread;
    sleep(3); // ENSURE PROPER SHUTDOWN OF THREADS
    return 0;
}

void shutdown(){
    for(pair<int, Thread*> thread : GameInstanceSingleton::getGameInstance().getThreadList()){
        delete thread.second;
    }
}