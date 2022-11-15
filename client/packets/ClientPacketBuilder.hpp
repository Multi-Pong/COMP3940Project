//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_CLIENTPACKETBUILDER_HPP
#define COMP3940PROJECT_CLIENTPACKETBUILDER_HPP

#include <string>

#define CRLF "\r\n"

class Player;

using namespace std;

/**
 * CLIENT SIDE
 */
class ClientPacketBuilder {
private:
public:
    ClientPacketBuilder() = default;
    /**
     * Builds packet using given params
     * @param id Id of player
     * @param xCoord x coordinate of player
     * @param yCoord y coordinate of player
     * @return Returns the completed Packet to send off.
     */
    static string buildPacket(const int id, const int xCoord, const int yCoord);

    /**
     *
     * @param player Player to send, in this case, the client itself.
     * @return Returns the completed Packet to send off.
     */
    static string buildPacket(const Player &player);


};


#endif //COMP3940PROJECT_CLIENTPACKETBUILDER_HPP
