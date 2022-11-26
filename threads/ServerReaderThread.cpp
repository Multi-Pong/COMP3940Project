//
// Created by Admin on 2022-11-14.
//

#include "ServerReaderThread.hpp"
#include <unistd.h>
#include <string>
#include <iostream>
#include "../server/packets/ServerPacketBuilder.hpp"
#include "../server/packets/ServerPacketReader.hpp"

#include "../game/GameInstanceSingleton.hpp"

ServerReaderThread::ServerReaderThread(Socket *sock) : Thread(this) {
    // All input from socket is read at this point.
    this->sock = sock;
}

void ServerReaderThread::run() {
    string str;
    string pattern;
    Player *p = nullptr;
    int playerId;
    char *buf = new char[1];
    do {
        memset(buf, 0, 1);
        delete p;
        p = nullptr;
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
        str += pattern;
        p = ServerPacketReader::readPacket(str);
        if (p != nullptr) {
            playerId = p->getID();
            if (p->getY() < 0) {
                p->setY(0);
            }
            if (p->getY() + PlayerHeight > FieldSizeHeight) {
                p->setY(FieldSizeHeight - PlayerHeight);
            }
            if (!GameInstanceSingleton::getGameInstance().playerExist(playerId)) {
                if (GameInstanceSingleton::getGameInstance().availableSpot() == -1) {
                    *buf = 0;
                } else {
                    pair<int, Thread *> pair = make_pair(playerId, this);
                    GameInstanceSingleton::getGameInstance().insertThread(pair);
                    GameInstanceSingleton::getGameInstance().assignSpot(p);
                    GameInstanceSingleton::getGameInstance().updatePlayerList(p);
                }
            } else {
                GameInstanceSingleton::getGameInstance().updatePlayerList(p);
            }
        }
    } while (*buf > 0);
    if (GameInstanceSingleton::getGameInstance().playerExist(playerId)) {
        GameInstanceSingleton::getGameInstance().playerDisconnect(playerId);
        string packet = ServerPacketBuilder::buildDisconnectPacket(playerId);
        GameInstanceSingleton::getGameInstance().notifyPlayers(packet);
    }
    delete p;
    delete[] buf;
    delete this; //Kill thread
}


ServerReaderThread::~ServerReaderThread() {
    cout << "DESTRUCT SOCKET THREAD" << endl;
    sock->close();
    delete sock;
}

void ServerReaderThread::send(string &packet) {
    sock->sendResponse(packet);
}

