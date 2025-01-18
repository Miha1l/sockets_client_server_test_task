#pragma once

#include <mutex>
#include <condition_variable>
#include <string>
#include <queue>

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
    void sendData(const std::string &value);

private:
    std::string ip;
    int port;
    int sock;
    struct sockaddr_in address;
    std::queue<std::string> buffer;
    std::mutex m;
    std::condition_variable cond_var;
    Handler handler;
};