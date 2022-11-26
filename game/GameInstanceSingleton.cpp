//
// Created by Admin on 2022-11-14.
//

#include "GameInstanceSingleton.hpp"
#include "../server/packets/ServerPacketBuilder.hpp"


GameInstanceSingleton::GameInstanceSingleton() {
//    localPlayer = new Player;
    ball = new Ball{FieldSizeWidth / 2, FieldSizeHeight / 2};
    points = new Points{0,0};
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
    } catch (out_of_range &e) {
        return false;
    }
}

void GameInstanceSingleton::notifyPlayers(string &packet) {
    for (pair<int, Thread *> pair: threadList) {
        pair.second->send(packet);
    }

}

bool GameInstanceSingleton::assignSpot(Player *p) {
    //TODO SET PLAYER POS ON ASSIGNMENT
    int spot;
    if ((spot = availableSpot()) > -1) {
        playerSpots[spot] = p->getID();
        p->setPlayerNumber(spot);
        return true;
    }
    return false;
}

bool GameInstanceSingleton::playerExist(const int playerId) const {
    for (int playerSpot: playerSpots) {
        if (playerSpot == playerId) return true;
    }
    return false;
}

int GameInstanceSingleton::availableSpot() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (playerSpots[i] <= 0) return i;
    }
    return -1;
}

void GameInstanceSingleton::playerDisconnect(int id) {
    playerSpots[getPlayerList().at(id).getPlayerNumber()] = 0;
    removePlayer(id);
    removeThread(id);
}
