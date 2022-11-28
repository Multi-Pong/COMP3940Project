//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_SERVERPACKETREADER_HPP
#define COMP3940PROJECT_SERVERPACKETREADER_HPP
#include <string>
#include "../../game/Player.hpp"
using namespace std;

class ServerPacketReader {
private:
public:
    static Player* readPacket(string packet);
};


#endif //COMP3940PROJECT_SERVERPACKETREADER_HPP
