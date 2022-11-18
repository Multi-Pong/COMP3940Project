//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
#define COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP

#include "Player.hpp"
#include <vector>
#include <map>
#include <iostream>

class SocketThread;

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
    Player* localPlayer = nullptr;

    // Container of currently connected Players in the Server.
    map<int,Player> playerList;
    map<int,SocketThread*> threadList;

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

    void setPlayer(Player* p){
        auto pos = playerList.find(p->getID());
        if(pos != playerList.end()){
            pos->second = *p;
        } else {
            playerList.insert(make_pair(p->getID(), *p));
        }
        if (p->getID() == localPlayer->getID()){
            localPlayer = p;
        }
    }

    // Setters
    void setLocalPlayer(Player* p){
        playerList.insert(make_pair(p->getID(), *p));
        this->localPlayer = p;
    }

    // Getters
    Player* getLocalPlayer(){ return this->localPlayer;}


    map<int,Player> getPlayerList(){return this->playerList;}
    map<int,SocketThread*> getThreadList(){return this->threadList;}

    // TODO: For Server to update playerList, Calls notifyAll after Update
    void updatePlayerList(Player *p);

//
//    // TODO: Update all Players in playerList of Server's state of the game.
//    void notifyPlayers();

    ~GameInstanceSingleton(){
        if(localPlayer != nullptr){
            delete localPlayer;
        }
    }
};


#endif //COMP3940PROJECT_GAMEINSTANCESINGLETON_HPP
