//
// Created by Admin on 2022-11-16.
//

#ifndef COMP3940PROJECT_CLIENTREADERTHREAD_HPP
#define COMP3940PROJECT_CLIENTREADERTHREAD_HPP


#include "Thread.hpp"
#include "../sockets/Socket.hpp"

class ClientReaderThread : public Thread{
private:
    Socket * sock;
public:
    ClientReaderThread(Socket * sock);
    void run() override;
    ~ClientReaderThread();
};


#endif //COMP3940PROJECT_CLIENTREADERTHREAD_HPP
