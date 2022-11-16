//
// Created by Admin on 2022-11-14.
//
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdio>
#include "Networking.hpp"
#include "packets/ClientPacketBuilder.hpp"
#include "packets/ClientPacketReader.hpp"

SOCKET ConnectSocket = INVALID_SOCKET;
double inputUpdateInterval = 1.0f/20.0f;
double lastNow = 0;
int n = 1;

void connect() {
    // https://stackoverflow.com/questions/4991967/how-does-wsastartup-function-initiates-use-of-the-winsock-dll
    // In the WSADATA that it populates, it will tell you what version it is offering you based on your request.
    // It also fills in some other information which you are not required to look at if you aren't interested.
    // You never have to submit this WSADATA struct to WinSock again, because it is used purely to give you feedback on your WSAStartup request.
    WSADATA wsaData;
    struct addrinfo *result = NULL,
            *ptr = NULL,
            hints;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
//    if (argc != 2) {
//        printf("usage: %s server-name\n", argv[0]);
//        return 1;
//    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
    }

    ZeroMemory(&hints, sizeof(hints)); // Set bits to 0
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_IP, to_string(DEFAULT_PORT).c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
//        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
//            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);


    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
//        return 1;
    }

    // Receive until the peer closes the connection
    // TODO put reader into thread or something
//    do {
//        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
//        if (iResult > 0) {
//            printf("Bytes received: %d\n", iResult);
//            ClientPacketReader reader;
//            string pack(recvbuf, recvbuf + iResult - 1);
//            reader.readPacket(pack);
//            vector<Player *> playerList = reader.getPlayers();
//            for (Player *p: playerList) {
//                cout << "Player " << p->getID() << ", X:" << p->getX() << ", Y:" << p->getY() << endl;
//            }
//        } else if (iResult == 0)
//            printf("Connection closed\n");
//        else
//            printf("recv failed with error: %d\n", WSAGetLastError());
//    } while (iResult > 0);
}

void update(double now, float deltaT) {
    // Send an initial buffer
    //TODO ADD if MOVED check
    cout << "SENDING"<< endl;
    if (now - lastNow > inputUpdateInterval) {

        // TODO Move packet send to game update
        string packet = ClientPacketBuilder::buildPacket(n, n, n);
        n += 1;
        cout << "PACKET:" << endl;
        cout << packet << endl;
        const char *sendbuf = packet.c_str();
        int iResult = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
        if (iResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
//        return 1;
        }
        printf("Bytes Sent: %ld\n", iResult);
        lastNow = now;
        // shutdown the connection since no more data will be sent
    }
    //TODO ADD PACKET READ

    cout << "READING"<< endl;
    //
    char *buf = new char[1];
    string str = "";
//    string pattern = "";
    int rval;
    while (buf[0] != '\4'){
        if ((rval = recv(ConnectSocket, buf, 1, 0)) < 0) {
            perror("reading socket");
            buf[0] = -1;
        }
        cout << *buf;
        if (buf[0] != '\4') {
//            str += pattern;
//            pattern = "";
            str += buf[0];
        }
//        } else {
//            pattern += buf[0];
//        }
//            cout << hex << (int) *buf << endl;
    }
//    str += pattern;
    delete buf;
    ClientPacketReader::readPacket(str);
}

bool isConnected() {
    //This might be wrong
    return (ConnectSocket != INVALID_SOCKET);
}

void disconnect() {
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
//        return 1;
    }
    closesocket(ConnectSocket);
    WSACleanup();
}
