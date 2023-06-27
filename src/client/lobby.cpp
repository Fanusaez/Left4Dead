#include "lobby.h"
#include <cstring>
#include "../common/instructionsDTO/create_dto.h"
#include "../common/instructionsDTO/join_dto.h"
#include <sys/socket.h>
#include <utility>
#include <string>
#include <arpa/inet.h>

Lobby::Lobby(char *localhost, char *puerto) : socket(localhost,puerto), queue_sender(1000000), 
            queue_receiver(1000000), keep_talking(true), 
            lobby_sender(&socket,std::ref(keep_talking),&queue_sender), 
            lobby_receiver(&socket,std::ref(keep_talking),&queue_receiver){
    bool was_closed = false;
    socket.recvall(&player_id,sizeof(int),&was_closed);
    player_id = ntohl(player_id);
    lobby_sender.start();
    lobby_receiver.start();
}

bool Lobby::create_scenario(const std::string& scenario_name, const GameMode& game_mode, const int8_t& game_players){
    return (queue_sender.try_push(lobby_serializer.serialize_create_scenario(scenario_name, game_mode, game_players)));
}

bool Lobby::join_scenario(const int32_t& scenario_code) {
    return (queue_sender.try_push(lobby_serializer.serialize_join_scenario(scenario_code)));
}

void Lobby::start() {
    queue_sender.try_push(lobby_serializer.serialize_start_playing());
}

void Lobby::soldier_type(const SoldierType& soldier_type) {
    queue_sender.try_push(lobby_serializer.serialize_soldier(soldier_type));
}

void Lobby::close() {
    keep_talking = false;
    socket.shutdown(SHUT_RDWR);
    socket.close();
    queue_sender.close();
    lobby_sender.join();
    queue_receiver.close();
    lobby_receiver.join(); 
}

void Lobby::exit_lobby() {
    keep_talking = false;
    queue_sender.close();
    lobby_sender.join();
    lobby_receiver.join(); 
}

Socket Lobby::move_socket(){
    return std::move(socket);
}

int32_t Lobby::get_create() {
    InstructionsDTO* instruction_dto = queue_receiver.pop();
    CreateDTO* create_dto = dynamic_cast<CreateDTO*>(instruction_dto);
    int32_t game_code = create_dto->get_game_code(); 
    delete instruction_dto;
    return game_code;
}

bool Lobby::get_join() {
    InstructionsDTO* instruction_dto = queue_receiver.pop();
    JoinDTO* join_dto = dynamic_cast<JoinDTO*>(instruction_dto);
    bool could_join = join_dto->get_could_join();
    delete join_dto;
    return could_join;
}

int Lobby::get_player_id(){
    return player_id;
}
