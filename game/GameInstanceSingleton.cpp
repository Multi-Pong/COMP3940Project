//
// Created by Admin on 2022-11-14.
//

#include "GameInstanceSingleton.hpp"
#include "../server/packets/ServerPacketBuilder.hpp"


GameInstanceSingleton::GameInstanceSingleton() {
//    localPlayer = new Player;
}

GameInstanceSingleton &GameInstanceSingleton::getGameInstance() {
    // Returning static instance of this class
    static GameInstanceSingleton instance;
    return instance;
}

void GameInstanceSingleton::updatePlayerList(Player *p) {
    try {
        Player *player = &playerList.at(p->getID());
        player->setX(p->getX());
        player->setY(p->getY());
    } catch (out_of_range &e) {
//        printf("ADDING PLAYER\n");
        playerList.insert(make_pair(p->getID(), *p));
    } catch (exception &e) {
        printf("Error: %s\n", e.what());
    }
}

bool GameInstanceSingleton::localHasMoved() {
    if (localPlayer == nullptr) {
        return false;
    }
    try {
        Player *p = &playerList.at(localPlayer->getID());
        return !(p->getX() == localPlayer->getX() && p->getY() == localPlayer->getY());
    } catch (out_of_range e) {
        return false;
    }
}

void GameInstanceSingleton::notifyPlayers(string packet) {
    for(pair<int, Thread*> pair : threadList){
        pair.second->send(packet);
    }

}
