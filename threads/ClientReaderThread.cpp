//
// Created by Admin on 2022-11-16.
//

#include <iostream>
#include "../client/packets/ClientPacketReader.hpp"
#include "ClientReaderThread.hpp"

using namespace std;

ClientReaderThread::ClientReaderThread(Socket *sock) : Thread(this) {
    this->sock = sock;
}

void ClientReaderThread::run() {
    cout << "READING" << endl;
    //
    char *buf = new char[1];
    string str;
    do {
        memset(buf, 0, 1);
        str = "";
//    string pattern = "";
        int rval;

        while (buf[0] != '\4' && (*(buf = sock->getNext()) > 0)) {
//            cout << (int) *buf;
            if (buf[0] != '\4') {
                str += buf[0];
            }
        }
        if (!str.empty())ClientPacketReader::readPacket(str);

    } while (*buf > 0);
    delete[] buf;
    delete this; // kill thread
}

ClientReaderThread::~ClientReaderThread() {
    cout << "DESTRUCT READER THREAD" << endl;
    delete sock;
    SOCKET s = INVALID_SOCKET;
    sock = new Socket(s);
}
