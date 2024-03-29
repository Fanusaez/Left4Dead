#include "lobby_deserializer.h"
#include <iostream>
#include <arpa/inet.h>

LobbyDeserializer::LobbyDeserializer(Socket *socket) : socket(socket) {}

InstructionsDTO* LobbyDeserializer::obtener_instruccion(bool *was_closed)
{
    char code = 0;
    socket->recvall(&code, 1, was_closed);
    if (*was_closed){
        throw std::runtime_error("Se cerro el socket esperando una instruccion");
    }
    InstructionsType instruction_type = static_cast<InstructionsType>(code);
    switch (instruction_type) {
        case CREATE:
            return (deserialize_create_scenario(was_closed));
            break;
        case JOIN:
            return (deserialize_join_scenario(was_closed));
            break;
        case START:
            return (deserialize_start_game(was_closed));
            break;
        }
}

/*----------------------Lobby message--------------------*/

CreateDTO* LobbyDeserializer::deserialize_create_scenario(bool *was_closed)
{
    int32_t game_code;
    socket->recvall(&game_code, 4, was_closed);
    game_code = ntohl(game_code);
    CreateDTO* create_dto = new CreateDTO(game_code);
    return create_dto;
}

JoinDTO* LobbyDeserializer::deserialize_join_scenario(bool *was_closed)
{
    bool could_join;
    socket->recvall(&could_join, 1, was_closed);
    JoinDTO* join_dto = new JoinDTO(could_join);
    return join_dto;
}

StartDTO* LobbyDeserializer::deserialize_start_game(bool *was_closed) {
    bool could_start;
    socket->recvall(&could_start, 1, was_closed);
    StartDTO* startDTO = new StartDTO(could_start);
    return startDTO; 
}
