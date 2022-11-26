//
// Created by Admin on 2022-11-10.
//

#ifndef COMP3940PROJECT_SOCKET_HPP
#define COMP3940PROJECT_SOCKET_HPP

#include <winsock2.h>
#include <vector>
#include <string>

using namespace std;

class Socket {
public:
    Socket(SOCKET &sock);

    char *getNext();

    void sendResponse(string &res);

    /**
     * Closes socket
     */
    void close() { closesocket(sock); }

    /**
     * Shutsdown socket
     * @return Int
     */
    int shutDown() { return shutdown(sock, SD_SEND); }

    bool isConnected();

    ~Socket();

    void dump(vector<char> &result);

private:
    SOCKET sock = INVALID_SOCKET;
};


#endif //COMP3940PROJECT_SOCKET_HPP
