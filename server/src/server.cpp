#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

Server::Server(int port) : port(port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 1) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    close(sock);
}

void Server::start() {
    while(1) {
        getData();
    }
}

void Server::getData() {
    auto fd = accept(sock, NULL, NULL);
    if (fd == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected\n";
    
    while (1) {
        auto bytes_read = recv(fd, buf, sizeof(buf), 0);
        if (bytes_read <= 0) {
            break;
        }

        processingData(std::string(buf));
    }

    close(fd);
}

void Server::processingData(const std::string &s) {
    std::vector<std::pair<char, int>> pairs;
    for (int i = 0; i < s.size(); ) {
        auto pos = s.find('\n', i);
        pairs.push_back({s[i], std::stoi(s.substr(i + 2, pos - i - 2))});
        i = pos + 1;
    }

    std::sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b) {
        return std::tie(a.second, a.first) < std::tie(b.second, b.first);
    });

    std::cout << "Getting data: ";
    for (const auto &[sym, count] : pairs) {
        std::cout << sym;
    }
    std::cout << '\n';
}