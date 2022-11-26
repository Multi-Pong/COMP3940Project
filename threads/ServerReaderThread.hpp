//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_SERVERREADERTHREAD_HPP
#define COMP3940PROJECT_SERVERREADERTHREAD_HPP

#include "Thread.hpp"
#include "../sockets/Socket.hpp"

class ServerReaderThread : public Thread{
private:
    Socket * sock;
public:
    ServerReaderThread(Socket * sock);
    void run() override;
    void send(string&) override;
    ~ServerReaderThread() override;
};


#endif //COMP3940PROJECT_SERVERREADERTHREAD_HPP
