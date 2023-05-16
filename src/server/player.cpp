#include "player.h"

#include <sys/socket.h>
#include <iostream>
#include <utility>

Player::Player(Socket socket,MatchMananger *matchMananger): 
        player_sender(&peer, std::ref(keep_talking),matchMananger)
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
    player_sender.join();
    player_sender.joinPlayerReceiver();
}