//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_CLIENTPACKETBUILDER_HPP
#define COMP3940PROJECT_PACKETBUILDER_HPP

#include <string>
#include <vector>

#define CRLF "\r\n"
#define DELIM "\r\n\r\n"
#define BOUNDARY "BOUNDARY!!!!!!!"

using namespace std;

class Player;

class ServerPacketBuilder {
private:
public:
    ServerPacketBuilder() = default;
    /**
     * Adds Body part to Packet for provided Player.
     * @param player
     * @return Body component of player
     */
    static string addPlayerBodyPart(const Player &player);

    /**
     * Builds packet using given params - Initial Testing for Packet Structure
     * @param id Id of player
     * @param xCoord x coordinate of player
     * @param yCoord y coordinate of player
     * @return Returns the completed Packet to send off.
     */
    static string addPlayerBodyPart(const int id, const int xCoord, const int yCoord);

    /**
     * Constructs Packet
     * @param playerList
     * @return Returns the Packet to send of to Client
     */
    static string buildPacket(vector<Player *> &playerList);

    /**
     * Constructs Packet
     * @return Returns the Packet to send of to Client
     */
    static string buildPacket();

    //TODO
    /**
     * Adds Ball Body Part to Packet Payload
     * @return Returns string to append onto Packet Payloac
     */
//   static string addBallBodyPart();
};


#endif //COMP3940PROJECT_CLIENTPACKETBUILDER_HPP
