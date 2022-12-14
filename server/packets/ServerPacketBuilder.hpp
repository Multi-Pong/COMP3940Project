//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_SERVERPACKETBUILDER_HPP
#define COMP3940PROJECT_PACKETBUILDER_HPP

#include <string>
#include <vector>

#define CRLF "\r\n"
#define BOUNDARY "BOUNDARY!!!!!!!"

using namespace std;

class Player;
class Ball;
class Points;

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
     * Constructs GameStatePacket
     * @return Returns the Packet to send off to Client
     */
    static string buildGameStatePacket();

    /**
     * Constructs Disconnect Packet
     * @param playerId Player that disconnected
     * @return Returns the Packet to send off to Client
     */
    static string buildDisconnectPacket(const int& playerId);

    //TODO
    /**
     * Adds Ball Body Part to Packet Payload
     * @return Returns string to append onto Packet Payload
     */
    static string addBallBodyPart(Ball);

    /**
     * Adds Points Body Part to Packet Payload
     * @return Returns string to append onto packet Payload
     */
     static string addPointsBodyPart(Points);
};


#endif //COMP3940PROJECT_SERVERPACKETBUILDER_HPP
