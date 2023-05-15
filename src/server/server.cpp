#include "server.h"
#include <sys/socket.h>
#include <iostream>

Server::Server(char* port) : server(port), acceptor(&server) {
    acceptor.start();
}

void Server::run(){
    while (getc(stdin) != 'q'){}
    server.shutdown(SHUT_RDWR);
    server.close();
    acceptor.join();
}
