#include "client_sender.h"

#include <iostream>
#include <vector>
#include <string>

#include <arpa/inet.h>

ClientSender::ClientSender(Socket *socket, std::atomic<bool> &keep_talking,Queue<std::vector<char>> *queue_sender) : 
    socket(socket), keep_talking(keep_talking), queue_sender(queue_sender){}

void ClientSender::run() {
    bool was_closed = false;
    std::vector<char> bytes;
    while (!was_closed  && keep_talking){
        bytes = queue_sender->pop();    //Otra forma es que popemos instrucciones y que aca tengamos un protoclo que las traduzca
        socket->sendall(bytes.data(), bytes.size(), &was_closed);
    }
    keep_talking = false;
}