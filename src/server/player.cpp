#include "player.h"

#include <sys/socket.h>
#include <iostream>
#include <utility>

Player::Player(Socket socket,MatchMananger *matchMananger): queue_sender(10000), 
        player_sender(&peer, std::ref(keep_talking), &queue_sender),
        player_receiver(&peer, matchMananger, queue_receiver,&queue_sender, std::ref(keep_talking))
{
    this->peer = std::move(socket);
    player_sender.start();
    player_receiver.start();    
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
    player_receiver.join();
}