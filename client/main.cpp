#define WIN32_LEAN_AND_MEAN

// include raylib
#include <unistd.h>
#include "raylib.h"
#include "Networking.hpp"

using namespace std;

int __cdecl main(int argc, char **argv) {
    // set up raylib
    InitWindow(FieldSizeWidth, FieldSizeHeight, "Client");
    SetTargetFPS(60);
    bool connected = false;
    float moveSpeed = 10;
    connect(); // Connect to server
    Vector2 movement = {0};
    while (!WindowShouldClose()) {
        cout << endl;
        cout << "MAIN LOOP" << endl;
        connected = isConnected();
        if (connected) {
//            connected = true;

            float speed = moveSpeed;

            // see what axes we move in
            if (IsKeyDown(KEY_UP))
                movement.y -= speed;
            if (IsKeyDown(KEY_DOWN))
                movement.y += speed;

            if (IsKeyDown(KEY_LEFT))
                movement.x -= speed;
            if (IsKeyDown(KEY_RIGHT))
                movement.x += speed;

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
            DrawRectangle((int) movement.x, (int) movement.y, PlayerSize, PlayerSize, WHITE);
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

