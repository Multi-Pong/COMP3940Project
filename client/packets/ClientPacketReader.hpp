//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_CLIENTPACKETREADER_HPP
#define COMP3940PROJECT_CLIENTPACKETREADER_HPP

#include "../../game/Player.hpp"
#include <vector>
#include <string>
using namespace std;

class ClientPacketReader {
private:
    vector<Player> players;
public:
    void readPacket(string packet);
    vector<Player> getPlayers();
};


#endif //COMP3940PROJECT_CLIENTPACKETREADER_HPP
