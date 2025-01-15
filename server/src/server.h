#pragma once

#include <netinet/in.h>

#define MULTIPLICITY 32

class Server {
public:
    Server(int port = 8080);
    ~Server();
    
    void start();
    void getData();
    void processingData(const int& sum);

private:
    int sock;
    int port;
    struct sockaddr_in address;
    int buf;

};