//
// Created by Admin on 2022-11-14.
//

#include "ClientPacketBuilder.hpp"
#include "../../game/Player.hpp"
string ClientPacketBuilder::buildPacket(const Player& player) {

    string packet;
    packet.append("id:").append(to_string(player.getID()));
    packet.append(CRLF);
    packet.append("xCoord:").append(to_string(player.getX()));
    packet.append(CRLF);
    packet.append("yCoord:").append(to_string(player.getY()));
    packet.append(CRLF).append(CRLF);
    packet.append("\4");
    return packet;
}

string ClientPacketBuilder::buildPacket(const int id, const int xCoord, const int yCoord) {
    string packet;
    packet.append("id:").append(to_string(id));
    packet.append(CRLF);
    packet.append("xCoord:").append(to_string(xCoord));
    packet.append(CRLF);
    packet.append("yCoord:").append(to_string(yCoord));
    packet.append(CRLF).append(CRLF);
    packet.append("\4");
    return packet;
}
