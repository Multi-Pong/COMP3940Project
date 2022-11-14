//
// Created by Admin on 2022-11-14.
//

#ifndef COMP3940PROJECT_NETWORKING_HPP
#define COMP3940PROJECT_NETWORKING_HPP

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#define DEFAULT_BUFLEN 512
#define DEFAULT_IP "localhost"
#define DEFAULT_PORT 8888

using namespace std;
// TODO pass IP and port as params
void connect();


#endif //COMP3940PROJECT_NETWORKING_HPP
