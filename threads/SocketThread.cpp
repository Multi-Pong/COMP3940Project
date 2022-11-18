//
// Created by Admin on 2022-11-14.
//

#include "SocketThread.hpp"
#include <unistd.h>
#include <string>
#include <iostream>
#include "../server/packets/ServerPacketBuilder.hpp"
#include "../server/packets/ServerPacketReader.hpp"

#include "../game/GameInstanceSingleton.hpp"

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
    char *buf = new char[1];
    do {
        memset(buf, 0, 1);
        str = "";
        pattern = "";
        while (buf[0] != '\4' && *(buf = sock->getNext()) > 0) {
            if (buf[0] != '\r' && buf[0] != '\n') {
                str += pattern;
                pattern = "";
                str += buf[0];
            } else {
                pattern += buf[0];
            }
//            cout << hex << (int) *buf << endl;
        }
        cout << "END OF WHILE: " << *buf << endl;
        str += pattern;
//        ServerPacketReader read;
//        cout << "READING PACKET" << endl;
//        cout << str << endl;
        Player *p = ServerPacketReader::readPacket(str);
//        Player p = read.getPlayer();
        if (p == nullptr) {
            cout << "NO PLAYER" << endl;
        } else {
            cout << "RECIEVED PLAYER" << endl;
            GameInstanceSingleton::getGameInstance().updatePlayerList(p);
            cout << *p << endl;
        }

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
    } while (*buf > 0);
    delete[] buf;
    delete this; //Kill thread
}

SocketThread::~SocketThread() {
    cout << "DESTRUCT SOCKET THREAD"<< endl;
    delete sock;
}
