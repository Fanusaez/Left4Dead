#include "player.h"

#include <sys/socket.h>
#include <iostream>
#include <utility>

Player::Player(Socket socket,MatchMananger *matchMananger, int32_t player_id) : player_id(player_id),
        player_sender(&peer, std::ref(stay_in_match), std::ref(keep_playing), matchMananger, player_id)
{
    this->peer = std::move(socket);
    player_sender.start();    
    stay_in_match = false;
    keep_playing = true;
}

bool Player::is_dead() {
    return not keep_playing;
}

void Player::kill() {
    //Con esto le digo a los hilos receiver y sender que corten el loop
    stay_in_match = false;
    keep_playing = false;
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
