#include "lobby_receiver.h"

#include <iostream>
#include <vector>
#include <string>

LobbyReceiver::LobbyReceiver(Socket *socket, std::atomic<bool> &keep_talking, Queue<InstructionsDTO> *queue_receiver) : 
    keep_talking(keep_talking),queue_receiver(queue_receiver),lobby_deserializer(socket) {}

void LobbyReceiver::run() {
    bool was_closed = false;
    while (keep_talking && was_closed == false) {
        InstructionsDTO instruction = lobby_deserializer.obtener_instruccion(&was_closed);
        queue_receiver->push(instruction);
    }
}