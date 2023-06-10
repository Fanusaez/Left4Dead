#include "lobby_sender.h"

#include <iostream>
#include <vector>
#include <string>

#include <arpa/inet.h>

LobbySender::LobbySender(Socket *socket, std::atomic<bool> &keep_talking,
                         Queue<std::vector<char>> *queue_sender) : 
    socket(socket), keep_talking(keep_talking), queue_sender(queue_sender){}

void LobbySender::run() {
    bool was_closed = false;
    std::vector<char> bytes;
    while (!was_closed  && keep_talking){
        try {
            bytes = queue_sender->pop();   
        } catch (const ClosedQueue& e){
            std::cout<<"Se cerro la cola correctamente"<<std::endl;
        }
        socket->sendall(bytes.data(), bytes.size(), &was_closed);
    }
    keep_talking = false;
}
