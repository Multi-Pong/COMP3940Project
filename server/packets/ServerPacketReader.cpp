//
// Created by Admin on 2022-11-14.
//

#include "ServerPacketReader.hpp"

#include <sstream>
#include <iostream>

Player *ServerPacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    Player *p = nullptr;
    int id =0, x=0, y=0;
    while (stream >> current) {
        istringstream breaker(current);
        string first;
        getline(breaker, first, ':');
        string second;
        getline(breaker, second);
        if (first == "id") {
            id = stoi(second);
        }
        if (first == "xCoord") {
            x = stoi(second);
        }
        if (first == "yCoord") {
            y = stoi(second);
        }
    }
    if ((id + x + y) > 0) {
        p = new Player{id, x, y};
    }
    return p;
}
