#include "Server.h"

Server::Server(int port) : port(port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        std::perror("Opening socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 1) == -1) {
        perror("Listen failed");
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
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Client connected\n";
    
    while (1) {
        auto bytesRead = recv(fd, &buf, sizeof(buf), 0);
        if (bytesRead <= 0) {
            break;
        }

        processingData(buf);
    }

    close(fd);
}

void Server::processingData(const int& sum) {
    if (std::to_string(sum).length() > 2 and sum % MULTIPLICITY == 0) {
        std::cout << "Data received successfully. Get value: " << sum << '\n';
        return;
    }

    std::cout << "Invalid data. Get value: " << sum << '\n';
}