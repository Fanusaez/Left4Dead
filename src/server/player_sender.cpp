#include "player_sender.h"
#include <string.h>

PlayerSender::PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, MatchMananger *match_mananger) : 
    keep_talking(keep_talking),queue_sender(10000), player_receiver(socket,match_mananger,keep_talking)
{
    this->match_mananger = match_mananger;
    this->socket = socket;
    keep_talking = true;
}
void PlayerSender::run() {
    initPlayerReceiver();
    bool was_closed = false;
    std::vector<char> bytes;
    while (keep_talking && was_closed == false) {
        std::vector<char> bytes;
        bool could_pop = queue_sender.try_pop(bytes);
        if (could_pop)
        socket->sendall(bytes.data(), bytes.size(), &was_closed);
    }
    keep_talking = false;
}

void PlayerSender::joinPlayerReceiver(){
    player_receiver.join();
}

void PlayerSender::initPlayerReceiver(){
    // Mientras no se le asigne partida
    while (queue_receiver == NULL)
    { 
        // socket->recev()
        // Recibo un creat o un join
        std::string mapa = "map123";
        queue_receiver = match_mananger->getQueueGame(&queue_sender, &mapa); // Es el caso de create despues hay que hacer una para join
    }
    player_receiver.setQueueReceiver(queue_receiver);
    // Una vez que se pudo unir a una partida lanzo el player_receiver
    player_receiver.start();
}