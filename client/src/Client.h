#pragma once

#include <cstdio>
#include <cctype>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <queue>
#include <regex>
#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory>
#include "Handler.h"

class Client {
private:
    std::string ip;
    int port;
    int sock;
    struct sockaddr_in address;
    std::queue<std::string> buffer;
    std::mutex m;
    std::condition_variable cond_var;
    Handler handler;

public:
    Client(std::string ip = "127.0.0.1", int port = 8080);
    ~Client();
    void connectToServer();
    void readData();
    void processingData();
    void start();
    void sendData(int& value);
};