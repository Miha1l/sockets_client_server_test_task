#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define MULTIPLICITY 32

class Server {
private:
    int sock;
    int port;
    struct sockaddr_in address;
    int buf;

public:
    Server(int port = 8080);
    ~Server();
    void start();
    void getData();
    void processingData(const int& sum);
};