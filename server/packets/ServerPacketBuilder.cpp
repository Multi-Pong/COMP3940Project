//
// Created by Admin on 2022-11-14.
//

#include "ServerPacketBuilder.hpp"

string ServerPacketBuilder::addPlayerBodyPart(const Player &player){
//    string playerBody;
//    playerBody.append(BOUNDARY).append(CRLF);
//    // Header
//    playerBody.append("Content-Type: Player").append(CRLF).append(CRLF);
//    // Payload (Nothing on this line)
//    playerBody.append("id:").append(to_string(player.getID())).append(CRLF);
//    playerBody.append("xCoord:").append(to_string(player.getX())).append(CRLF);
//    playerBody.append("yCoord:").append(to_string(player.getY())).append(CRLF).append(CRLF);
//    return playerBody;
}

//TODO change to gameState object for variable types
string ServerPacketBuilder::constructPacket(vector<Player *> &playerList) {
    string packet;
    packet.append(BOUNDARY).append(CRLF);
    // append contentType
    for(Player *p : playerList){
        packet.append(addPlayerBodyPart(*p));
    }
    // Delimit End Of Packet
    packet.append(BOUNDARY).append(CRLF).append(CRLF);
    return packet;
}

string ServerPacketBuilder::addPlayerBodyPart(const int id, const int xCoord, const int yCoord) {
    string playerBody;
    playerBody.append(BOUNDARY).append(CRLF);
    // Header
    playerBody.append("Content-Type: Player").append(CRLF).append(CRLF);
    // Payload (Nothing on this line)
    playerBody.append("id:").append(to_string(id)).append(CRLF);
    playerBody.append("xCoord:").append(to_string(xCoord)).append(CRLF);
    playerBody.append("yCoord:").append(to_string(yCoord)).append(CRLF).append(CRLF);
    return playerBody;
}
