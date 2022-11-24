//
// Created by Admin on 2022-11-16.
//

#ifndef COMP3940PROJECT_CLIENTREADERTHREAD_HPP
#define COMP3940PROJECT_CLIENTREADERTHREAD_HPP


#include "Thread.hpp"
#include "../sockets/Socket.hpp"

class ClientReaderThread : public Thread{
private:
    Socket * sock = nullptr;
    int *threadRunning;
public:
    ClientReaderThread(Socket ** sock, int *threadRunning);
    void run() override;
    void send(string&) override;
    ~ClientReaderThread() override;
};


#endif //COMP3940PROJECT_CLIENTREADERTHREAD_HPP
