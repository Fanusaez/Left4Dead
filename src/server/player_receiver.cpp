#include "player_receiver.h"

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

#include <arpa/inet.h>

PlayerReceiver::PlayerReceiver(Socket *socket, MatchMananger *match_manager, std::atomic<bool> &keep_talking) : 
    match_manager(match_manager), keep_talking(keep_talking) {
        this->queue_receiver = queue_receiver;
    }

void PlayerReceiver::run() {
    bool was_closed = false;
    //Recibo instruccion y la pusheo a queue receiver que pertenece al hilo Game
    std::vector<char> bytes = {0, 0, 0, 0};
    queue_receiver->push(bytes);
}

void PlayerReceiver::setQueueReceiver(Queue<std::vector<char>> *queue_receiver){
    this->queue_receiver = queue_receiver;
}