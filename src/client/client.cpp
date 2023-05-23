#include "client.h"


Client::Client(char *localhost, char *puerto) : socket(localhost, puerto), queue_sender(10000), queue_receiver(10000),
    client_sender(&socket,std::ref(keep_talking),&queue_sender), client_receiver(&socket,std::ref(keep_talking),&queue_receiver) {
    client_sender.start();
    client_receiver.start();
    keep_talking = true;        
}

bool Client::create_scenario(const std::string& scenario_name){
    return (queue_sender.try_push(client_seializer.serialize_create_scenario(scenario_name)));
}

bool Client::join_scenario(const int32_t& scenario_code)
{
    return (queue_sender.try_push(client_seializer.serialize_join_scenario(scenario_code)));
}

bool Client::move(Move move)
{
    return (queue_sender.try_push(client_seializer.serialize_move(move)));
}

GameDTO Client::get_game(){
    GameDTO game_dto;
    queue_receiver.try_pop(game_dto);
    return game_dto;
}

void Client::join()
{
    socket.close();
    queue_sender.close(); // Es correcto hacer eso?
    client_sender.join();
    queue_receiver.close(); // Es correcto hacer eso?
    client_receiver.join();
}
