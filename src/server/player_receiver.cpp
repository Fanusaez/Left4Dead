#include "player_receiver.h"

#include <iostream>
#include <vector>
#include <string>
#include "player.h"

#include <arpa/inet.h>

PlayerReceiver::PlayerReceiver(Socket *socket, MatchMananger *match_manager, 
    Queue<std::vector<char>> *queue_receiver, Queue<std::vector<char>> *queue_sender, std::atomic<bool> &keep_talking) : 
    match_manager(match_manager), queue_receiver(queue_receiver),queue_sender(queue_sender),
    keep_talking(keep_talking) {}

void PlayerReceiver::run() {
    bool was_closed = false;
    while (queue_receiver == NULL){ //Mientras no se le asigne partida
        //socket->recev()
        //Recibo un creat o un join
        std::string mapa = "map123";
        queue_receiver = match_manager->crear(queue_sender, &mapa); //En el caso de create despues hay que hacer una para join
    }
}
