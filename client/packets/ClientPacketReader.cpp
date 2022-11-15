//
// Created by Admin on 2022-11-14.
//

#include "PacketReader.hpp"
#include <sstream>

void PacketReader::readPacket(string packet) {
    istringstream stream(packet);
    string current;
    while(stream >> current){

    }
}
