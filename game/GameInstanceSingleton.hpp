//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
#define COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP

#include <vector>
#include <map>
#include <iostream>
#include "Player.hpp"
#include "../threads/Thread.hpp"

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

    // TODO Implement Ball.
    // Ball* ball;

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
    void notifyPlayers(string packet);

    ~GameInstanceSingleton() {
        delete localPlayer;
    }
};


#endif //COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
