//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
#define COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP


#include "Player.hpp"
#include "Ball.hpp"
#include "Points.hpp"

#include <vector>
#include <map>
#include <iostream>
#include "Player.hpp"
#include "../threads/Thread.hpp"


#define MAX_PLAYERS 8
// how big the screen is for all players
#define FieldSizeWidth 1280
#define FieldSizeHeight  800

// how big a player is
#define PlayerWidth 10
#define PlayerHeight 80
#define BallRadius 5

using namespace std;

/*
 * Holds the current instance of the game, to be referenced by multiple clients.
 * Observer - Subject Model.
 */
class GameInstanceSingleton {
private:
    // Hiding Default Constructor
    // TODO Write default game state
    GameInstanceSingleton();

    // For clients to update their current position to this Singleton
    Player *localPlayer = nullptr;

    // Container of currently connected Players in the Server.
    map<int, Player> playerList;
    map<int, Thread *> threadList;

    //TODO Implement player availability array
    //TODO Implement player number ie. Player 1, Player 2, etc.
    int playerSpots[MAX_PLAYERS];

    // TODO Implement Ball.
     Ball* ball = nullptr;

    // TODO Implement Score.
    // Member Variables
    int teamOnePoints;
    int teamTwoPoints;

public:
    /*
     * Delete the Copy Constructor
     */
    GameInstanceSingleton(GameInstanceSingleton &) = delete;

    /*
     * Delete the ability to use the assignment operator
     */
    void operator=(GameInstanceSingleton const &) = delete;

    // Getter for the GameInstance
    static GameInstanceSingleton &getGameInstance();

    void setPlayer(Player *p) {
        auto pos = playerList.find(p->getID());
        if (pos != playerList.end()) {
            pos->second = *p;
        } else {
            playerList.insert(make_pair(p->getID(), *p));
        }
        if (p->getID() == localPlayer->getID()) {
            localPlayer = p;
        }
    }

    void setBall(Ball *b) {
        ball = b;
    }

    Ball* getBall(){
        return ball;
    };

    // Setters
    void setLocalPlayer(Player *p) {
        playerList.insert(make_pair(p->getID(), *p));
        this->localPlayer = p;
    }

    void insertThread(pair<int, Thread *> &pair) {
        threadList.insert(pair);
    }

    // Getters
    Player *getLocalPlayer() { return this->localPlayer; }


    /**
     * @return List of all players
     */
    map<int, Player> getPlayerList() { return this->playerList; }

    /**
     * @return List of all threads
     */
    map<int, Thread *> getThreadList() { return this->threadList; }

    /**
     *
     * @param playerId
     * @return
     */
    bool playerExist(const int playerId) const ;

    /**
     * Gets first available spot in playerSpots
     * @return Index of first available spot, -1 otherwise
     */
    int availableSpot();

    /**
     * Assigns given player a player spot
     * @param p Player to assign
     * @return True if player was given position in playerSpots
     */
    bool assignSpot(Player *p);

    /**
     * Clears instance of given player id
     * @param id
     */
    void playerDisconnect(int id);

    /**
     * Removes player by given id
     * @param id Id of player
     */
    void removePlayer(int id) {
        if (playerList.count(id) > 0) playerList.erase(id);
    }

    /**
     * Removes Thread by associated player id
     * @param id Id of player attached to thread
     */
    void removeThread(int id) {
        if (threadList.count(id) > 0) threadList.erase(id);
    }

    /**
     * Updates playerList with given player pointer
     * Adds if player does not already exist in list
     * @param p Pointer to player to be updated in list
     */
    void updatePlayerList(Player *p);

    /**
     * Check if local player position is different to matching player in playerList
     * @return
     */
    bool localHasMoved();

    /**
     * Sends packet to all connected players
     * @param packet Packet to be sent
     */
    void notifyPlayers(string &packet);

    ~GameInstanceSingleton() {
        delete localPlayer;
        delete ball;
    }
};


#endif //COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
