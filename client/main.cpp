#define WIN32_LEAN_AND_MEAN

// include raylib
#include <unistd.h>
#include "raylib.h"
#include "Networking.hpp"
#include "../game/GameInstanceSingleton.hpp"

using namespace std;

const float MOVE_SPEED = 10;
/*
 * TODO For Client to update Local Player
 * Update Observer - GameInstance
 */
void clientUpdateGameInstance(){

    float speed = MOVE_SPEED;

    // see what axes we move in
    if (IsKeyDown(KEY_UP))
        GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeY(-speed);
    if (IsKeyDown(KEY_DOWN))
        GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeY(speed);
    if (IsKeyDown(KEY_LEFT))
        GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeX(-speed);
    if (IsKeyDown(KEY_RIGHT))
        GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeX(speed);
}

//
//    // TODO: [Response as Client updates theirs]For Client to update their Game State
//    void receiveServerState();

int __cdecl main(int argc, char **argv) {
    GameInstanceSingleton::getGameInstance();
    Player clientPlayer{1, 5, 5};
    GameInstanceSingleton::getGameInstance().setLocalPlayer(&clientPlayer);
    // set up raylib
    InitWindow(FieldSizeWidth, FieldSizeHeight, "Client");
    SetTargetFPS(60);
    bool connected = false;

    connect(); // Connect to server
    while (!WindowShouldClose()) {
        cout << endl;
        cout << "MAIN LOOP" << endl;

        if (isConnected()) {
            connected = true;
            clientUpdateGameInstance();
            /*
//            float speed = moveSpeed;
//
//            // see what axes we move in
//            if (IsKeyDown(KEY_UP))
////                movement.y -= speed;
//            GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeY(-speed);
////                GameInstanceSingleton::getGameInstance().setLocalPlayer(clientPlayer);
//            if (IsKeyDown(KEY_DOWN))
//                movement.y += speed;
//
//            if (IsKeyDown(KEY_LEFT))
//                movement.x -= speed;
//            if (IsKeyDown(KEY_RIGHT))
//                movement.x += speed;
             */

            cout << "UPDATING: " << connected << endl;
            update(GetTime(), GetFrameTime());

        } else {
            cout << "RECONNECTING" << endl;
            connect();
//            connected = false;
        }

        cout << "DRAWING" << endl;
        BeginDrawing();
        ClearBackground(BLACK);

        if (!connected) {
            // we are not connected, so just wait until we are, this can take some time
            DrawText("Connecting", 0, 20, 20, RED);
        } else {
            DrawText("Connected", 0, 20, 20, LIME);
            DrawRectangle((int) GameInstanceSingleton::getGameInstance().getLocalPlayer()->getX(), (int) GameInstanceSingleton::getGameInstance().getLocalPlayer()->getY(), PlayerSize, PlayerSize, WHITE);
        }
        DrawFPS(0, 0);
        EndDrawing();
//        sleep(5);
    }

    CloseWindow();
    disconnect();
    sleep(3);
    return 0;
}

