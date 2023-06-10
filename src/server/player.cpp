#include "player.h"

#include <sys/socket.h>
#include <iostream>
#include <utility>

Player::Player(Socket socket,MatchMananger *matchMananger, int player_id) : player_id(player_id),
        player_sender(&peer, std::ref(keep_talking),matchMananger, &(this->player_id))
{
    this->peer = std::move(socket);
    player_sender.start();    
    keep_talking = true;
}

bool Player::is_dead() {
    return not keep_talking;
}

void Player::kill() {
    keep_talking = false;
    peer.shutdown(SHUT_RDWR);
    peer.close();
}

void Player::join(){
    player_sender.close_queue(); //Es correcto hacer eso?
    player_sender.join();
    player_sender.join_player_receiver();
}
