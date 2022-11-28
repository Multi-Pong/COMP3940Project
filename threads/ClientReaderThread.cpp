//
// Created by Admin on 2022-11-16.
//

#include <iostream>
#include "../client/packets/ClientPacketReader.hpp"
#include "ClientReaderThread.hpp"

using namespace std;

ClientReaderThread::ClientReaderThread(Socket **sock, int *threadRunning) : Thread(this) {
    this->sock = *sock;
    this->threadRunning = threadRunning;
}

void ClientReaderThread::run() {
    *threadRunning = 1;
    //
    char *buf = new char[1];
    string str;
    do {
        memset(buf, 0, 1);
        str = "";
        while (buf[0] != '\4' && (*(buf = sock->getNext()) > 0)) {
            if (buf[0] != '\4') {
                str += buf[0];
            }
        }
        if (!str.empty()) { ClientPacketReader::readPacket(str); }

    } while (*buf > 0);
    delete[] buf;
    delete this; // kill thread
}

ClientReaderThread::~ClientReaderThread() {
    cout << "DESTRUCT READER THREAD" << endl;
    if (*threadRunning) {
        *threadRunning = 0;
        auto s = INVALID_SOCKET;
        auto *deadS = new Socket(s);
        Socket tmp = *sock;
        *sock = *deadS;
    }

}

void ClientReaderThread::send(string&) {
    //DO NOTHING
}
