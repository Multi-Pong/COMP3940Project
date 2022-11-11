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

    if ((rval = recv(sock, buf, 1, 0) < 0)) {
        perror("reading socket");
        buf[0] = -1;
        return buf;
    }
    return buf;
}

void Socket::sendResponse(char *res) {
    int rval;

    if ((rval = send(sock, res, strlen(res), 0)) < 0) {
        perror("writing socket");
    } else {
        printf("%s\n", res);
    }

    return;
}

Socket::~Socket() {}

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