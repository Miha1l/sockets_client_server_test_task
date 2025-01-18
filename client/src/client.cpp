#include <iostream>
#include <chrono>
#include <thread>
#include <cerrno>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "client.h"

Client::Client(std::string ip, int port) : ip(ip), port(port) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    auto res = inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    if (res == 0) {
        // perror("inet_pton");
        exit(EXIT_FAILURE);
    } else if (res == -1) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    connectToServer();
}

Client::~Client() {
    close(sock);
}

void Client::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    while (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    std::cout << "Connected to server\n";
}

void Client::readData() {
    while (1) { 
        std::string data;
        std::getline(std::cin, data);

        if (!handler.check(data)) {
            std::cout << "String is incorrect\n";
            continue;
        }

        std::unique_lock<std::mutex> locker(m);
        buffer.push(data);
        locker.unlock();
        cond_var.notify_one();
    }
}

void Client::processingData() {
    while (1) {
        std::unique_lock<std::mutex> locker(m);
        cond_var.wait(locker, [&](){
            return buffer.size();
        });

        const auto data = buffer.front();
        
        auto result_str = handler.process(data);
        std::cout << "Processed data:\n" << result_str;

        buffer.pop();
        locker.unlock();

        sendData(result_str);
    }
}

void Client::start() {
    std::thread t1(&Client::readData, this);
    std::thread t2(&Client::processingData, this);

    t1.join();
    t2.join();
}

void Client::sendData(const std::string &value) {
    while(1) {
        auto send_bytes = send(sock, value.c_str(), value.size() + 1, MSG_NOSIGNAL);

        if (errno == EPIPE) {
            close(sock);
            connectToServer();
            continue;
        }

        if (send_bytes == -1) {
            continue;
        }
        
        break;
    }

}