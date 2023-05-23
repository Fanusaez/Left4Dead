#include "player_sender.h"
#include <string.h>

PlayerSender::PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, MatchMananger *match_mananger, int* player_id) : 
    keep_talking(keep_talking),queue_sender(10000), player_receiver(socket,match_mananger,keep_talking, player_id),
    match_mananger(match_mananger), server_deserializer(socket), server_serializer(socket), player_id(player_id)
{
    keep_talking = true;
}

void PlayerSender::run() {
    init_player_receiver();
    GameDTO game_dto;
    std::vector<char> bytes;
    while (keep_talking && was_closed == false) {
        game_dto = queue_sender.pop();
        server_serializer.send_game(game_dto, &was_closed);
    }
    keep_talking = false;
}

void PlayerSender::join_player_receiver(){
    player_receiver.join();
}

void PlayerSender::close_queue() {
    queue_sender.close();
}

void PlayerSender::init_player_receiver(){
    // Mientras no se le asigne partida
    while (queue_receiver == NULL){
        Instructions instruction = server_deserializer.obtener_instruccion(&was_closed);
        if (instruction == CREATE){
            std::string game_name = server_deserializer.deserialize_create(&was_closed);
            queue_receiver = match_mananger->create_game(&queue_sender, &game_name, player_id);
        } else if (instruction == JOIN){
            int32_t game_code = server_deserializer.deserialize_join(&was_closed);
            queue_receiver = match_mananger->join(&queue_sender, &game_code, player_id);
        }
    }
    //Le digo al player receiver la queueu que tiene que usar
    player_receiver.setQueueReceiver(queue_receiver);
    // Una vez que se pudo unir a una partida lanzo el player_receiver
    player_receiver.start();
}