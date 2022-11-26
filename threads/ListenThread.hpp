//
// Created by Admin on 2022-11-21.
//

#ifndef COMP3940PROJECT_LISTENTHREAD_HPP
#define COMP3940PROJECT_LISTENTHREAD_HPP


#include "Thread.hpp"

class ServerSocket;

class ListenThread : public Thread {
private:
    ServerSocket *ListenSocket;
public:
    ListenThread();
    void run() override;
    void send(std::string&) override;
    ~ListenThread() override;
};


#endif //COMP3940PROJECT_LISTENTHREAD_HPP
