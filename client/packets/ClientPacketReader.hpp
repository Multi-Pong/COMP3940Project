//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_CLIENTPACKETREADER_HPP
#define COMP3940PROJECT_CLIENTPACKETREADER_HPP

#include "../../game/Player.hpp"
#include <vector>
#include <string>

#define BOUNDARY "BOUNDARY!!!!!!!"
#define CRLF "\r\n"


using namespace std;

class ClientPacketReader {
public:
    static void readPacket(string packet);
};


#endif //COMP3940PROJECT_CLIENTPACKETREADER_HPP
