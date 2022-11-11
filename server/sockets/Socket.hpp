//
// Created by Admin on 2022-11-10.
//

#ifndef COMP3940PROJECT_SOCKET_HPP
#define COMP3940PROJECT_SOCKET_HPP

#include <winsock2.h>
#include <vector>

using namespace std;
class Socket {
public:
    Socket(SOCKET &sock);

    /**
     * Returns next char
     */
    char *getNext();
    void sendResponse(char *res);
    void close() { closesocket(sock);}
    int shutDown(){return shutdown(sock, SD_SEND);}
    ~Socket();
    void dump(vector<char> &result);

private:
    SOCKET sock;
};


#endif //COMP3940PROJECT_SOCKET_HPP
