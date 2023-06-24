#include "client.h"
#include <sys/socket.h>
#include <utility>

Client::Client(Socket&& peer) : queue_sender(1000000), queue_receiver(1000000), keep_talking(true),
    client_sender(&socket,std::ref(keep_talking),&queue_sender), 
    client_receiver(&socket,std::ref(keep_talking),&queue_receiver), socket(std::move(peer)) {
    client_sender.start();
    client_receiver.start();
    start_playing();
}

void Client::start_playing(){
    queue_sender.try_push(client_seializer.serialize_start_playing());
}

bool Client::move(const MoveType move){
    return (queue_sender.try_push(client_seializer.serialize_move(move)));
}

bool Client::reload(){
    return (queue_sender.try_push(client_seializer.serialize_reloading()));
}

bool Client::shoot(){
    return (queue_sender.try_push(client_seializer.serialize_shooting()));
}

bool Client::throw_explosive_grenade(const int32_t& time){
    return (queue_sender.try_push(client_seializer.serialize_throw_explosive_grenede(time)));
}

bool Client::throw_smoke_grenade(const int32_t& time){
    return (queue_sender.try_push(client_seializer.serialize_throw_smoke_grenede(time)));
}

bool Client::call_air_strike(){
    return (queue_sender.try_push(client_seializer.serialize_call_air_strike()));
}

bool Client::revive_soldier(){
    return (queue_sender.try_push(client_seializer.serialize_revive_soldier()));
}

std::optional<GameDTO> Client::get_game(){
    GameDTO game_dto;
    if (queue_receiver.try_pop(game_dto)) {
        return std::optional<GameDTO> (game_dto);
    } else {
        return std::optional<GameDTO> ();
    }
}

void Client::join(){
    socket.shutdown(SHUT_RDWR);
    socket.close();
    queue_sender.close(); // Es correcto hacer eso?
    client_sender.join();
    queue_receiver.close(); // Es correcto hacer eso?
    client_receiver.join(); 
}
