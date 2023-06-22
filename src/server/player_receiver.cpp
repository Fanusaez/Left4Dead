#include "player_receiver.h"

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

#include <arpa/inet.h>

PlayerReceiver::PlayerReceiver(Socket *socket, std::atomic<bool> &stay_in_match,
                             std::atomic<bool> &keep_playing, int32_t& player_id) 
    : player_id(player_id), stay_in_match(stay_in_match), keep_playing(keep_playing),
    server_deserializer(socket) {
        queue_receiver = nullptr;   //Comienza en nullptr. El player_sender le va a setear la queue
    }

void PlayerReceiver::run() {
    bool was_closed = false;
    while (stay_in_match && was_closed == false) {
        try {
            InstructionsDTO* new_instructionsDTO = server_deserializer.obtener_instruccion(&was_closed,player_id);
            try {
                queue_receiver->push(new_instructionsDTO);
            } catch (const ClosedQueue& e){
                delete new_instructionsDTO;
                std::cout<<"Juego finalizado"<<std::endl;
                break;
            }
        } catch (const std::runtime_error& e) {
            keep_playing = false;
            std::cout<<"Se desconecto el cliente"<<std::endl;
            break;
        }
    }
    stay_in_match = false;
}

void PlayerReceiver::setQueueReceiver(Queue<InstructionsDTO*> *queue_receiver){
    this->queue_receiver = queue_receiver;
}
