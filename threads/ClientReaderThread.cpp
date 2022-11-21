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
//    cout << "READING" << endl;
    //
    char *buf = new char[1];
    string str;
    do {
        memset(buf, 0, 1);
        str = "";
//    string pattern = "";
        int rval;

        while (buf[0] != '\4' && (*(buf = sock->getNext()) > 0)) {
//            cout <<  str;
            if (buf[0] != '\4') {
                str += buf[0];
            }
        }
//        cout << "RECV" << endl;
//        cout << str << endl;
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
//        cout << sock << " "<< sock->isConnected() << endl;
    }

}

void ClientReaderThread::send(string) {
    //DO NOTHING
}
