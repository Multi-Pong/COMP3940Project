//
// Created by Admin on 2022-11-14.
//

#include "GameInstanceSingleton.hpp"

GameInstanceSingleton::GameInstanceSingleton() {
//    localPlayer = new Player;
}

GameInstanceSingleton& GameInstanceSingleton::getGameInstance(){
    // Returning static instance of this class
    static GameInstanceSingleton instance;
    return instance;
}
