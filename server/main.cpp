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
//#include "../threads/ServerReaderThread.hpp"
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
#include "packets/ServerPacketBuilder.hpp"


// Process one frame of updates
void update(double, float);

void shutdown();


double lastNow = 0;
bool gameBegin = false;

int __cdecl main() {
    GameInstanceSingleton::getGameInstance();
    auto *listenThread = new ListenThread{};
    listenThread->start();

    InitWindow(FieldSizeWidth, FieldSizeHeight, "Server");
    SetTargetFPS(60);
//    Ball* startBall = new Ball(FieldSizeWidth/2, FieldSizeHeight/2);
//    GameInstanceSingleton::getGameInstance().setBall(startBall);
    while (!WindowShouldClose()) {

        //Game logic
        update(GetTime(), GetFrameTime());

        //Draw Frame
        BeginDrawing();
        ClearBackground(BLACK);
        DrawLineEx(Vector2{FieldSizeWidth / 2, 0}, Vector2{FieldSizeWidth / 2, FieldSizeHeight}, 5, WHITE);
        for (pair<const int, Player> x: GameInstanceSingleton::getGameInstance().getPlayerList()) {
            //TODO SET PLAYER COLOUR
            DrawRectangle((int) x.second.getX(), (int) x.second.getY(), PlayerWidth, PlayerHeight, WHITE);
        }
        //Draw Ball
        Ball *b = GameInstanceSingleton::getGameInstance().getBall();
        DrawCircle(b->getXCoord(), b->getYCoord(), BallRadius, WHITE);

        //Draw Score
        Points *p = GameInstanceSingleton::getGameInstance().getPoints();
        DrawText(to_string(p->getTeamOnePoints()).c_str(), FieldSizeWidth * 0.25, 10, 20, WHITE);
        DrawText(to_string(p->getTeamTwoPoints()).c_str(), FieldSizeWidth * 0.75, 10, 20, WHITE);

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    shutdown();
    delete listenThread;
    sleep(3); // ENSURE PROPER SHUTDOWN OF THREADS
    return 0;
}

// Process one frame of updates
void update(double now, float deltaT) {
    if (now - lastNow > INPUT_UPDATE_INTERVAL) {
        Ball *b = GameInstanceSingleton::getGameInstance().getBall();
        if (!gameBegin && GameInstanceSingleton::getGameInstance().getPlayerList().size() > 1) {
            //START GAME
            gameBegin = true;
            if (b->getXSpeed() == 0 && b->getYSpeed() == 0) {
                b->setXSpeed(3);
            }
        }

        vector<Rectangle *> playerHitboxes;
        for (pair<const int, Player> x: GameInstanceSingleton::getGameInstance().getPlayerList()) {
            playerHitboxes.push_back(
                    new Rectangle{static_cast<float>(x.second.getX()), static_cast<float>(x.second.getY()), PlayerWidth,
                                  PlayerHeight});
        }

        Rectangle ballHitbox{static_cast<float>(b->getXCoord()), static_cast<float>(b->getYCoord()), BallRadius * 2,
                             BallRadius * 2};
        for (Rectangle *hb: playerHitboxes) {
            if (hb->x <= ballHitbox.x && hb->x + hb->width >= ballHitbox.x) {
                if (hb->y <= ballHitbox.y && hb->y + hb->height / 3 > ballHitbox.y) {
                    b->setXSpeed(b->getXSpeed() * -1.3);
                    b->setYSpeed((b->getYSpeed() * -1.2) - 5);
                }
                if (hb->y + hb->height / 3 <= ballHitbox.y && (hb->y + (2 * hb->height / 3)) > ballHitbox.y) {
                    b->setXSpeed(b->getXSpeed() * -1.3);
                    b->setYSpeed(b->getYSpeed() * -1.2);
                }
                if (hb->y + (2 * hb->height / 3) <= ballHitbox.y && hb->y + hb->height > ballHitbox.y) {
                    b->setXSpeed(b->getXSpeed() * -1.3);
                    b->setYSpeed((b->getYSpeed() * -1.2) + 5);
                }
            }
//            if(CheckCollisionRecs(*hb, ballHitbox)){
//                b->setXSpeed(b->getXSpeed() * -1.2);
//                b->setYSpeed(b->getYSpeed() * -1.2);
//            }
        }
        if (b->getYCoord() < BallRadius) {
            b->setYCoord(BallRadius);
            b->setYSpeed(b->getYSpeed() * -1);
        }
        if (b->getYCoord() + BallRadius > FieldSizeHeight) {
            b->setYCoord(FieldSizeHeight - BallRadius);
            b->setYSpeed(b->getYSpeed() * -1);
        }

        if (b->getXCoord() + BallRadius > FieldSizeWidth) {
            //ball exits right
            GameInstanceSingleton::getGameInstance().getPoints()->incrementTeamOnePoints();
            b->setXCoord(FieldSizeWidth / 2);
            b->setYSpeed(0);
            b->setXSpeed(-3);
        }

        if (b->getXCoord() < BallRadius) {
            //ball exits left
            GameInstanceSingleton::getGameInstance().getPoints()->incrementTeamTwoPoints();
            b->setXCoord(FieldSizeWidth / 2);
            b->setYSpeed(0);
            b->setXSpeed(3);
        }

        b->setXCoord(b->getXCoord() + b->getXSpeed());

        b->setYCoord(b->getYCoord() + b->getYSpeed());

//        cout << "SENDING" << endl;
        string packet = ServerPacketBuilder::buildGameStatePacket();
        GameInstanceSingleton::getGameInstance().notifyPlayers(packet);
        lastNow = now;
    }
}

void shutdown() {
    for (pair<int, Thread *> thread: GameInstanceSingleton::getGameInstance().getThreadList()) {
        delete thread.second;
    }
}