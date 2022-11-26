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
//    if (IsKeyDown(KEY_LEFT))
//        GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeX(-speed);
//    if (IsKeyDown(KEY_RIGHT))
//        GameInstanceSingleton::getGameInstance().getLocalPlayer()->changeX(speed);
}

int __cdecl main(int argc, char **argv) {
    GameInstanceSingleton::getGameInstance();
//    Ball* startBall = new Ball(5, 5);
//    GameInstanceSingleton::getGameInstance().setBall(startBall);
    srand(time(nullptr));
    Player clientPlayer{(int) floor(rand() * 10.0), (int)floor(rand() % FieldSizeWidth), FieldSizeHeight/2};
    GameInstanceSingleton::getGameInstance().setLocalPlayer(&clientPlayer);
    // set up raylib
    InitWindow(FieldSizeWidth, FieldSizeHeight, "Client");
    SetTargetFPS(60);
    bool connected = false;

    connect(); // Connect to server
    while (!WindowShouldClose()) {
        cout << endl;
//        cout << "MAIN LOOP" << endl;
        connected = isConnected();
        if (connected) {
            clientUpdateGameInstance();

//            cout << "UPDATING: " << connected << endl;
            update(GetTime(), GetFrameTime());

        } else {
//            cout << "RECONNECTING" << endl;
            connect();
//            connected = false;
        }

//        cout << "DRAWING" << endl;
        BeginDrawing();
        ClearBackground(BLACK);

        if (!connected) {
            // we are not connected, so just wait until we are, this can take some time
            DrawText("Connecting", 0, 20, 20, RED);
        } else {
            //Player number
            DrawText(TextFormat("Player %d", GameInstanceSingleton::getGameInstance().getLocalPlayer()->getPlayerNumber()), 0, 20, 20, LIME);
            //Mid line
            DrawLineEx(Vector2{FieldSizeWidth / 2, 0}, Vector2{FieldSizeWidth / 2, FieldSizeHeight}, 5, WHITE);
            //Players
            for (pair<const int, Player> x: GameInstanceSingleton::getGameInstance().getPlayerList()) {
                //TODO SET PLAYER COLOUR
                DrawRectangle((int) x.second.getX(), (int) x.second.getY(), PlayerWidth, PlayerHeight, WHITE);
            }
            //Draw Ball
            Ball* b = GameInstanceSingleton::getGameInstance().getBall();
            DrawCircle(b->getXCoord(), b->getYCoord(), BallRadius, WHITE);
            //Draw Score
            Points *p = GameInstanceSingleton::getGameInstance().getPoints();
            DrawText(to_string(p->getTeamOnePoints()).c_str(), FieldSizeWidth * 0.25, 10, 20, WHITE);
            DrawText(to_string(p->getTeamTwoPoints()).c_str(), FieldSizeWidth * 0.75, 10, 20, WHITE);
        }
        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    disconnect();
    sleep(3); // ENSURE PROPER SHUTDOWN OF THREADS
    return 0;
}

