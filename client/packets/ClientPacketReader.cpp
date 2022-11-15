//
// Created by Admin on 2022-11-14.
//

#include "ClientPacketReader.hpp"
#include <sstream>

void ClientPacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    while(stream >> current){

    }
}
