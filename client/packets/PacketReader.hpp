//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_PACKETREADER_HPP
#define COMP3940PROJECT_PACKETREADER_HPP


#include "../../game/Player.hpp"
#include <vector>
#include <string>
using namespace std;

class PacketReader {
private:
    vector<Player> players;
public:
    void readPacket(string packet);
    vector<Player> getPlayers();
};


#endif //COMP3940PROJECT_PACKETREADER_HPP
