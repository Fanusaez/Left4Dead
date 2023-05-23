#include "player_receiver.h"

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

#include <arpa/inet.h>

PlayerReceiver::PlayerReceiver(Socket *socket, MatchMananger *match_manager, std::atomic<bool> &keep_talking, int* player_id) : player_id(player_id),
    match_manager(match_manager), keep_talking(keep_talking), server_deserializer(socket),  queue_receiver(queue_receiver) {
    }

void PlayerReceiver::run() {
    bool was_closed = false;
    Instructions instruction;
    while (keep_talking && was_closed == false) {
        instruction = server_deserializer.obtener_instruccion(&was_closed);
        switch (instruction) {
        case MOVE:
            queue_receiver->push(server_deserializer.deserialize_move(&was_closed, player_id));
            break;
        case RELOAD:
            queue_receiver->push(server_deserializer.deserialize_reloading(&was_closed));
            break;
        case SHOOT:
            queue_receiver->push(server_deserializer.deserialize_shooting(&was_closed));
            break;
        case GRANEDE:
            queue_receiver->push(server_deserializer.deserialize_grenede(&was_closed));
            break;
        }
    }
}

void PlayerReceiver::setQueueReceiver(Queue<InstructionsDTO> *queue_receiver){
    this->queue_receiver = queue_receiver;
}