#include "lobby_receiver.h"

#include <iostream>
#include <vector>
#include <string>

LobbyReceiver::LobbyReceiver(Socket *socket, std::atomic<bool> &keep_talking, 
    Queue<InstructionsDTO*> *queue_receiver) : keep_talking(keep_talking),
    queue_receiver(queue_receiver),lobby_deserializer(socket) {}

void LobbyReceiver::run() {
    bool was_closed = false;
    while (keep_talking && was_closed == false) {
        try {
            InstructionsDTO* instruction = lobby_deserializer.obtener_instruccion(&was_closed);
            if (instruction->get_instruction() == START){
                StartDTO* start_dto = dynamic_cast<StartDTO*>(instruction);
                if (start_dto->get_could_start())
                    keep_talking = false;
            }
            queue_receiver->push(instruction);
        }
        catch (const std::runtime_error& e) {
            keep_talking = false;
            std::cout<<"Se desconecto el cliente"<<std::endl;
            break;
        }
    }
}
