#define WIN32_LEAN_AND_MEAN

// include raylib
#include <unistd.h>
#include <cmath>
#include "raylib.h"
#include "Networking.hpp"
#include "../game/GameInstanceSingleton.hpp"

using namespace std;

const float MOVE_SPEED = 10;

/*
 * Update Observer - GameInstance
 */
void clientUpdateGameInstance() {
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

int __cdecl main(int argc, char **argv) {
    GameInstanceSingleton::getGameInstance();
    srand(time(nullptr));
    Player clientPlayer{(int) floor(rand() * 10.0), 5, 5};
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
//            DrawText("Connected", 0, 20, 20, LIME);
            DrawText(TextFormat("Player %d", GameInstanceSingleton::getGameInstance().getLocalPlayer()->getPlayerNumber()), 0, 20, 20, LIME);
            for (pair<const int, Player> x: GameInstanceSingleton::getGameInstance().getPlayerList()) {
//                cout << x.second.getID() << endl;
                DrawRectangle((int) x.second.getX(), (int) x.second.getY(), PlayerSize, PlayerSize, WHITE);
            }
            //TODO Draw Ball
            //TODO Draw Score
        }
        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    disconnect();
    sleep(3); // ENSURE PROPER SHUTDOWN OF THREADS
    return 0;
}

