#include "player_sender.h"
#include <string.h>

PlayerSender::PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, 
        Queue<std::vector<char>> *q) : keep_talking(keep_talking),q(q)
{
    this->socket = socket;
    keep_talking = true;
}

void PlayerSender::run() {
    bool was_closed = false;
    std::vector<char> bytes;
    while (keep_talking && was_closed == false) {
        bytes = q->pop();
        socket->sendall(bytes.data(), bytes.size(), &was_closed);
    }
    keep_talking = false;
}
