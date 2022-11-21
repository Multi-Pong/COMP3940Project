//
// Created by Admin on 2022-11-14.
//

#include "ClientPacketReader.hpp"
#include "../../game/GameInstanceSingleton.hpp"
#include <sstream>
#include <iostream>

void ClientPacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    Player *p = nullptr;
    while (getline(stream, current)) {
//        cout << "Line: " << current << endl;
        istringstream breaker(current);
        string first;
        getline(breaker, first, ':');
        string second;
        getline(breaker, second, '\r');
        if (current == "Content-Type:Player\r") {
            p = new Player();
        }
        if (first == "id") {
            p->setID(stoi(second));
        }
        if (first == "xCoord") {
            p->setX(stoi(second));
        }
        if (first == "yCoord") {
            p->setY(stoi(second));
        }
        if (p != nullptr && current == "BOUNDARY!!!!!!!\r") {
            //players.push_back(p);
            //TODO add ball and score as well, once those are being sent
//            cout << "PLAYER RECV" << endl;
//            cout << *p << endl;
            GameInstanceSingleton::getGameInstance().setPlayer(p);
            if (GameInstanceSingleton::getGameInstance().getLocalPlayer()->getID() == p->getID()){
                GameInstanceSingleton::getGameInstance().setLocalPlayer(p);
            }
        }
    }
//    cout << "END READER" << endl;
}
