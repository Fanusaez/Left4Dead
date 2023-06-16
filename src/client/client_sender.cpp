#include "client_sender.h"

#include <iostream>
#include <vector>
#include <string>

#include <arpa/inet.h>

ClientSender::ClientSender(Socket *socket, std::atomic<bool> &keep_talking,
                            Queue<std::vector<char>> *queue_sender) : 
    socket(socket), keep_talking(keep_talking), queue_sender(queue_sender){}

void ClientSender::run() {
    bool was_closed = false;
    std::vector<char> bytes;
    try {
    	while (!was_closed  && keep_talking){
            bytes = queue_sender->pop();   
        	socket->sendall(bytes.data(), bytes.size(), &was_closed);
    	}
    } catch (const ClosedQueue& e){
        std::cout<<"Se cerro la cola correctamente"<<std::endl;
    }
    keep_talking = false;
}
