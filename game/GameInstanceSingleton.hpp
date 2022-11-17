//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
#define COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP

#include "Player.hpp"
#include <vector>

/*
 * Holds the current instance of the game, to be referenced by multiple clients.
 * Observer - Subject Model.
 */
class GameInstanceSingleton {
public:
    // Member Variables
    int teamOnePoints;
    int teamTwoPoints;

    // Container of currently connected Players in the Server.
    vector<Player> playerList;

    // TODO Implement Ball.
    // Ball ball;

    // For clients to update their current position to this Singleton
    Player localPlayer;

    // TODO: For Server to update playerList, Calls notifyAll after Update
    void serverUpdateGameInstance();

    // TODO: Update all Players in playerList of Server's state of the game.
    void notifyPlayers();

    // TODO: For Client to pull Game State
    void getGameState();

    // TODO For Client to update Local Player
    void clientUpdateGameInstance();

    // TODO: For Client to update their Game State
    void receiveServerState();

};


#endif //COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
