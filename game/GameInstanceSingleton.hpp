//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
#define COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP

#include "Player.hpp"
#include <vector>
#include <map>

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

//    static volatile GameInstanceSingleton instance = NULL;

    // Member Variables
    int teamOnePoints;
    int teamTwoPoints;

    // For clients to update their current position to this Singleton
    Player* localPlayer;

    // Container of currently connected Players in the Server.
    map<int,Player> playerList;

    // TODO Implement Ball.
    // Ball ball;
public:

    /*
     * Delete the Copy Constructor
     */
    GameInstanceSingleton(GameInstanceSingleton&) = delete;

    /*
     * Delete the ability to use the assignment operator
     */
    void operator=(GameInstanceSingleton const&) = delete;

    // Getter for the GameInstance
    static GameInstanceSingleton& getGameInstance();

    // Setters
    void setLocalPlayer(Player* p){
        playerList.insert(make_pair(p->getID(), *p));
        this->localPlayer = p;
    }

    // Getters
    Player* getLocalPlayer(){ return this->localPlayer;}

//    // TODO: For Server to update playerList, Calls notifyAll after Update
//    void serverUpdateGameInstance();
//
//    // TODO: Update all Players in playerList of Server's state of the game.
//    void notifyPlayers();

};


#endif //COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
