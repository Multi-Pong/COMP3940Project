//
// Created by Admin on 2022-11-16.
//

#include <iostream>
#include "../client/packets/ClientPacketReader.hpp"
#include "ClientReaderThread.hpp"

using namespace std;

ClientReaderThread::ClientReaderThread(Socket *sock) : Thread(this), sock(sock) {
}

void ClientReaderThread::run() {
    cout << "READING"<< endl;
    //
    char *buf = new char[1];
    string str = "";
//    string pattern = "";
    int rval;
    while (buf[0] != '\4', (*(buf = sock->getNext()) < 0)){
        cout << *buf;
        if (buf[0] != '\4') {
//            str += pattern;
//            pattern = "";
            str += buf[0];
        }
//        } else {
//            pattern += buf[0];
//        }
//            cout << hex << (int) *buf << endl;
    }
//    str += pattern;
    delete buf;
//    ClientPacketReader::readPacket(str);
}

ClientReaderThread::~ClientReaderThread() {

}
