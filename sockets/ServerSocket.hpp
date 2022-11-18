//
// Created by Admin on 2022-11-10.
//

#ifndef COMP3940PROJECT_SERVERSOCKET_HPP
#define COMP3940PROJECT_SERVERSOCKET_HPP

#include <winsock2.h>
#include "Socket.hpp"

class ServerSocket {
public:
    ServerSocket(int);

    Socket *Accept();

    void close() { closesocket(sock); }

    ~ServerSocket();

private:
    SOCKET sock;
};


#endif //COMP3940PROJECT_SERVERSOCKET_HPP
