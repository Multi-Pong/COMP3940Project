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
    static void readPlayer(istringstream&, string &);
    static void readDisconnect(istringstream&, string &);
    static void readBall(istringstream &stream, string &current);
    static void readPoints(istringstream &stream, string &current);
};


#endif //COMP3940PROJECT_CLIENTPACKETREADER_HPP
