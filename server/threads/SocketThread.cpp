//
// Created by Admin on 2022-11-14.
//

#include "SocketThread.hpp"
#include <unistd.h>
#include <string>
#include <iostream>
#include "../packets/ServerPacketBuilder.hpp"
#include "../packets/ServerPacketReader.hpp"

#include "../../game/GameInstanceSingleton.hpp"

SocketThread::SocketThread(Socket *sock) : Thread(this) {
//    request.setSocket(sock);
//    request.parse();

    // All input from socket is read at this point.
    this->sock = sock;
}

void SocketThread::run() {

    // Create Container to hold message
    vector<char> result;
    // Dump every char from Payload into vector. Vector now holds entire Payload.
//    sock->dump(result);
//    string buildMessage = "";
    string str;
    string pattern;
    while (true) {
        char *buf = new char[1];
        str = "";
        pattern = "";
        while (buf[0] != '\4' && *(buf = sock->getNext()) > 0 ) {
            cout << *buf;
            if (buf[0] != '\r' && buf[0] != '\n') {
                str += pattern;
                pattern = "";
                str += buf[0];
            } else {
                pattern += buf[0];
            }
//            cout << hex << (int) *buf << endl;
        }
        cout << "END OF WHILE: " <<*buf << endl;
        str += pattern;
        delete buf;
        ServerPacketReader read;
        cout << "READING PACKET" << endl;
        cout << str << endl;
        read.readPacket(str);
        Player p = read.getPlayer();
        cout << "RECIEVED PLAYER" << endl;
        cout << p << endl;

        //TODO Replace with buiildPacket
        string packet;
        packet.append(BOUNDARY).append(CRLF);
        // append contentType

        packet.append(ServerPacketBuilder::addPlayerBodyPart(1, 2, 3));

        // Delimit End Of Packet
        packet.append(BOUNDARY).append(CRLF).append(CRLF);
        packet.append("\4");
//        char responseCharArray[packet.length()];
//        strncpy(responseCharArray, packet.c_str(), packet.length());
        sock->sendResponse(packet);
    }
}

SocketThread::~SocketThread() {
    delete sock;
}
