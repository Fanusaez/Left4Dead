#include "client_receiver.h"

#include <iostream>
#include <vector>
#include <string>

#include "../common/instructions_type.h"

ClientReceiver::ClientReceiver(Socket *socket, std::atomic<bool> &keep_talking,
    Queue<GameDTO> *queue_receiver) : client_deserializer(socket), 
    keep_talking(keep_talking), queue_receiver(queue_receiver) {}

void ClientReceiver::run() {
    bool was_closed = false;
    InstructionsType instruction;
    std::vector<char> bytes;
    while (!was_closed && keep_talking) {
        GameDTO game_dto = client_deserializer.deserialize_game_dto(&was_closed);
        try {
            queue_receiver->push(game_dto); //Podemos pasarle los bytes o generar una estructura
        } catch (const ClosedQueue& e){
            std::cout<<"Se cerro la cola correctamente"<<std::endl;
        }
    }
}
