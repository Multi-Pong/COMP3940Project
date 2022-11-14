#define WIN32_LEAN_AND_MEAN

// include raylib
#include "raylib.h"
#include "Networking.hpp"

using namespace std;

int __cdecl main(int argc, char **argv) {
    // set up raylib
    InitWindow(FieldSizeWidth, FieldSizeHeight, "Client");
    SetTargetFPS(60);
    bool connected = false;
    Connect(); // Connect to server
    while(!WindowShouldClose()){
        if (Connected()){
            connected = true;
        } else {
            Connect();
            connected = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (!Connected())
        {
            // we are not connected, so just wait until we are, this can take some time
            DrawText("Connecting", 0, 20, 20, RED);
        } else {
            DrawText("Connected", 0, 20, 20, LIME);
        }
        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
    Disconnect();
    return 0;
}

