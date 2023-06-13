#include "player_receiver.h"

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

#include <arpa/inet.h>

PlayerReceiver::PlayerReceiver(Socket *socket, std::atomic<bool> &keep_talking, int& player_id) 
    : player_id(player_id), keep_talking(keep_talking), 
    server_deserializer(socket) {
        queue_receiver = nullptr;   //Comienza en nullptr. El player_sender le va a setear la queue
    }

void PlayerReceiver::run() {
    bool was_closed = false;
    while (keep_talking && was_closed == false) {
        try {
            queue_receiver->push(server_deserializer.obtener_instruccion(&was_closed,player_id));
        } 
        catch (const std::runtime_error& e) {
            keep_talking = false;
            break;
        }
    }
}

void PlayerReceiver::setQueueReceiver(Queue<InstructionsDTO*> *queue_receiver){
    this->queue_receiver = queue_receiver;
}
