#include "player_sender.h"
#include <string.h>

PlayerSender::PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, MatchMananger *match_mananger, int* player_id) : 
    keep_talking(keep_talking),queue_sender(10000), player_receiver(socket,match_mananger,keep_talking, player_id),
    match_mananger(match_mananger), server_deserializer(socket), server_serializer(socket), player_id(player_id)
{
    queue_receiver = nullptr;
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
    match_mananger->delete_player(player_id);
}

void PlayerSender::join_player_receiver(){
    if(queue_receiver != nullptr){
        queue_receiver->close();
        player_receiver.join();  
    }
}

void PlayerSender::close_queue() {
    queue_sender.close();
}

void PlayerSender::init_player_receiver(){
    // Mientras no se le asigne partida
    int32_t game_code;
    while (keep_talking){
        InstructionsDTO instruction = server_deserializer.obtener_instruccion(&was_closed,player_id);
        if(was_closed)
            return;
        if (instruction.get_instruction() == CREATE) {
            std::vector<char> parameters = instruction.get_parameters();
            std::string game_name(parameters.begin(), parameters.end());
            queue_receiver = match_mananger->create_game(&queue_sender, &game_name, player_id, &game_code);
            if (queue_receiver == nullptr)
                server_serializer.send_error_create(&was_closed);
            else
                server_serializer.serialize_create_scenario(game_code, &was_closed);
        } else if (instruction.get_instruction() == JOIN){
            game_code = *reinterpret_cast<int32_t*>(instruction.get_parameters().data());
            queue_receiver = match_mananger->join(&queue_sender, &game_code, player_id);
            server_serializer.serialize_join_scenario((queue_receiver != nullptr), &was_closed);
        } else if (instruction.get_instruction() == START){
            server_serializer.serialize_start_game(&was_closed);
            break;
        }
    }
    //Le digo al player receiver la queueu que tiene que usar
    player_receiver.setQueueReceiver(queue_receiver);
    // Una vez que se pudo unir a una partida lanzo el player_receiver
    player_receiver.start();
}