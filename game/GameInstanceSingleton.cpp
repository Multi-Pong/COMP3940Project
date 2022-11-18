//
// Created by Admin on 2022-11-14.
//

#include "GameInstanceSingleton.hpp"

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
        printf("ADDING PLAYER\n");
        playerList.insert(make_pair(p->getID(), *p));
    } catch (exception &e) {
        printf("Error: %s\n", e.what());
    }
}
