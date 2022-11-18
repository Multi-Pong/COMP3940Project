//
// Created by Admin on 2022-11-10.
//

#include "Socket.hpp"

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include <unistd.h>
#include <stdio.h>
#include <iostream>

Socket::Socket(SOCKET &sock) {
    this->sock = sock;
}

char *Socket::getNext() {
    int rval; // Return value
    char *buf = new char[1];
    if ((rval = recv(sock, buf, 1, 0)) < 0) {
        perror("reading socket");
        buf[0] = -1;
        return buf;
    }
    return buf;
}

void Socket::sendResponse(string res) {
    int rval;

    printf("SENDING: \n%s\n", res.c_str());
    if ((rval = send(sock, res.c_str(), strlen(res.c_str()), 0)) < 0) {
        perror("writing socket");
    } else {
        printf("%s\n", res.c_str());
    }

    return;
}

bool Socket::isConnected() {
    //This might be wrong
//    int error;
//    socklen_t len = sizeof(error);
//    int retval = getsockopt(this->sock, SOL_SOCKET, SO_ERROR, (char *) &error, &len);
//    if (retval != SOCKET_ERROR) {
//        /* there was a problem getting the error code */
////        fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
//        return true;
//    }
////
//    if (error != 0) {
//        /* socket has a non zero error status */
//        fprintf(stderr, "socket error: %s\n", strerror(error));
//        return false;
//    }
//    return false;
//    FD_SET m_readFds;
//    FD_ZERO(&m_readFds);
    return (sock != INVALID_SOCKET);
}

Socket::~Socket() {
    fprintf(stdout, "FREE SOCKET\n");
}

/**
 * DAAMM code you got a lot of DUMP!
 * That code do so much in so little code.
 */
void Socket::dump(std::vector<char> &result) {
    int rval;
    char *buf;

    while (*(buf = getNext()) > 0) {
        result.push_back(*buf);
    }

    delete buf;
}

