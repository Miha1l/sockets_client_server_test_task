#pragma once

#include <string>

#include <netinet/in.h>

#define BUFFER_SIZE 100

class Server {
public:
    Server(int port = 8080);
    ~Server();
    
    void start();
    void getData();
    void processingData(const std::string &s);

private:
    int sock;
    int port;
    struct sockaddr_in address;
    char buf[BUFFER_SIZE];
};