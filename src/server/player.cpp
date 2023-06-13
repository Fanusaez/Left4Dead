#include "player.h"

#include <sys/socket.h>
#include <iostream>
#include <utility>

Player::Player(Socket socket,MatchMananger *matchMananger, int player_id) : player_id(player_id),
        player_sender(&peer, std::ref(keep_talking),matchMananger, player_id)
{
    this->peer = std::move(socket);
    player_sender.start();    
    keep_talking = true;
}

bool Player::is_dead() {
    return not keep_talking;
}

void Player::kill() {
    //Con esto le digo a los hilos receiver y sender que corten el loop
    keep_talking = false;
    //Les cierro y le hago shutdown al socket
    peer.shutdown(SHUT_RDWR);
    peer.close();
    //Tambien le cierro la queue al player_sender en caso de que se haya quedado trabado
    player_sender.close_queue(); 
}

void Player::join(){
    player_sender.join();
    player_sender.join_player_receiver();
}
