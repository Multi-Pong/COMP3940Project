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
    // All input from socket is read at this point.
    this->sock = sock;
}

void SocketThread::run() {
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
        }
        cout << "END OF WHILE: " << *buf << endl;
        str += pattern;
        Player *p = ServerPacketReader::readPacket(str);
        if (p == nullptr) {
            cout << "NO PLAYER" << endl;
        } else {
            cout << "RECIEVED PLAYER" << endl;
            cout << *p << endl;
            if(GameInstanceSingleton::getGameInstance().getThreadList().find(p->getID()) == GameInstanceSingleton::getGameInstance().getThreadList().end()){
                GameInstanceSingleton::getGameInstance().getThreadList().insert(make_pair(p->getID(), this));
            }
            GameInstanceSingleton::getGameInstance().updatePlayerList(p);
        }

        //TODO Move to notifyPlayers()
        string packet = ServerPacketBuilder::buildPacket();
        sock->sendResponse(packet);
    } while (*buf > 0);
    delete[] buf;
    delete this; //Kill thread
}

SocketThread::~SocketThread() {
    cout << "DESTRUCT SOCKET THREAD"<< endl;
    delete sock;
}
