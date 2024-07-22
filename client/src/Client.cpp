#include "Client.h"

Client::Client(std::string ip, int port) : ip(ip), port(port) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    auto res = inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    if (res == 0) {
        std::perror("inet_pton failed: not a valid network address\n");
        exit(EXIT_FAILURE);
    } else if (res == -1) {
        std::perror("inet_pton failed");
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
        std::perror("Error opening socket");
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
        getline(std::cin, data);

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

        auto message = buffer.front();
        handler.process(message);
        std::cout << "Transformed message: " << message << '\n';

        auto sum = handler.getSum(message);
        buffer.pop();
        locker.unlock();
        sendData(sum);
    }
}

void Client::start() {
    std::thread t1(&Client::readData, this);
    std::thread t2(&Client::processingData, this);

    t1.join();
    t2.join();
}

void Client::sendData(int& value) {
    while(1) {
        auto sendBytes = send(sock, &value, sizeof(value), MSG_NOSIGNAL);
        if (errno == 32) {
            close(sock);
            connectToServer();
            continue;
        }
        
        if (sendBytes == -1) {
            continue;
        }

        break;
    }

}