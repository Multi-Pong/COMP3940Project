//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_PACKETREADER_HPP
#define COMP3940PROJECT_PACKETREADER_HPP
#include <string>
#include "../../game/Player.hpp"

using namespace std;

class PacketReader {
private:
    Player p;
public:
    void readPacket(string packet);
    Player getPlayer();
};


#endif //COMP3940PROJECT_PACKETREADER_HPP
