//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_SOCKETTHREAD_HPP
#define COMP3940PROJECT_SOCKETTHREAD_HPP

#include "Thread.hpp"
#include "../sockets/Socket.hpp"

class SocketThread : public Thread{
private:
    Socket * sock;
public:
    SocketThread(Socket * sock);
    void run() override;
    ~SocketThread();
};


#endif //COMP3940PROJECT_SOCKETTHREAD_HPP
