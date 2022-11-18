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

/**
 * Reads the next character in the socket, blocks until character is received
 * @return Character received
 */
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

/**
 * Writes string to socket
 * @param res String to write
 */
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

/**
* Checks if current socket is of type INVALID_SOCKET
* @return True if not INVALID_SOCKET
*/
bool Socket::isConnected() {
    //This might be wrong
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

