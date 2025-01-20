#pragma once

#include <mutex>
#include <condition_variable>
#include <string>

#include <netinet/in.h>

#include "handler.h"

class Client {
public:
    Client(std::string ip = "127.0.0.1", int port = 8080);
    ~Client();
    
    void connectToServer();
    void readData();
    void processingData();
    void start();
    void sendData(const std::string &data);

private:
    std::string ip;
    int port;
    int sock;
    struct sockaddr_in address;
    std::string buffer;
    std::mutex m;
    std::condition_variable cond_var;
    Handler handler;
};