//
// Created by Admin on 2022-11-14.
//

#include "ServerPacketReader.hpp"

#include <sstream>
#include <iostream>

void ServerPacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    while(stream >> current){
        istringstream breaker(current);
        string first;
        getline(breaker, first, ':');
        string second;
        getline(breaker, second);
        if (first == "id"){
            p.setID(stoi(second));
            cout << "HERE1 : " << second;
        }
        if (first == "xCoord"){
            p.setX(stoi(second));
            cout << "HERE2 : " << second;
        }
        if (first == "yCoord"){
            p.setY(stoi(second));
            cout << "HERE3 : " << second;
        }
    }
}

Player ServerPacketReader::getPlayer() {
    return p;
}
