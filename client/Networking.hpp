//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_NETWORKING_HPP
#define COMP3940PROJECT_NETWORKING_HPP

#include <iostream>
#include <cstdlib>
#include <cstdio>

// constants
#define DEFAULT_BUFLEN 512
#define DEFAULT_IP "localhost"
#define DEFAULT_PORT 8888

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;

// TODO pass IP and port as params
void connect();

// Process one frame of updates
void update(double, float);

// Disconnect from the server
void disconnect();

// True if we are connected to the server and have a valid player id.
bool isConnected();

// Tell the network game play how far we wanted to move this frame
//void updateLocalPlayer(Vector2* movementDelta, float deltaT);

// get the id that the server assigned to us
//int getLocalPlayerId();

// get the position info for a player from the local simulation that has the latest network data in it
// returns false if the player id is not valid
//bool getPlayerPos(int id, Vector2* pos);

#endif //COMP3940PROJECT_NETWORKING_HPP
