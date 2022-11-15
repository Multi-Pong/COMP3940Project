//
// Created by Admin on 2022-11-14.
//

#include "PacketReader.hpp"
#include "../../client/packets/PacketReader.hpp"

#include <sstream>

void PacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    while(stream >> current){
        istringstream breaker(current);
        string first;
        getline(breaker, first, ':');
        string second;
        getline(breaker, second, '\r');
        if (first == "id"){
            p.setID(stoi(second));
        }
        if (first == "xCoord"){
            p.setX(stoi(second));
        }
        if (first == "yCoord"){
            p.setY(stoi(second));
        }
    }
}

vector <Player> PacketReader::getPlayers() {
    return nullptr;
}

Player PacketReader::getPlayer() {
    return p;
}
