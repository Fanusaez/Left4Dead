#include "lobby_deserializer.h"
#include <iostream>

LobbyDeserializer::LobbyDeserializer(Socket *socket) : socket(socket) {}

InstructionsDTO LobbyDeserializer::obtener_instruccion(bool *was_closed)
{
    char code = 0;
    socket->recvall(&code, 1, was_closed);
    Instructions instruction = static_cast<Instructions>(code);
    switch (instruction) {
        case CREATE:
            return (deserialize_create_scenario(was_closed));
            break;
        case JOIN:
            return (deserialize_join_scenario(was_closed));
            break;
        case GAME_LIST:
            return (deserialize_game_list(was_closed));
            break;
        case START:
            InstructionsDTO instruction;
            return instruction;
            //return (deserialize_start_game(was_closed));
            break;
        }
}

/*----------------------Lobby message--------------------*/

InstructionsDTO LobbyDeserializer::deserialize_create_scenario(bool *was_closed)
{
    std::vector<char> buffer(4);
    socket->recvall(buffer.data(), 4, was_closed);
    InstructionsDTO instructionsDTO(CREATE, buffer);
    return instructionsDTO;
}

InstructionsDTO LobbyDeserializer::deserialize_join_scenario(bool *was_closed)
{
    std::vector<char> buffer(1);
    socket->recvall(buffer.data(), 1, was_closed);
    InstructionsDTO instructionsDTO(JOIN, buffer);
    return instructionsDTO;
}

InstructionsDTO LobbyDeserializer::deserialize_game_list(bool *was_closed) {
    int games;
    socket->recvall(&games, 1, was_closed);
    std::vector<char> buffer(games*5); //Code + cantidad de personas
    socket->recvall(&buffer, games*5, was_closed);
    InstructionsDTO instructionsDTO(GAME_LIST, buffer);
    return instructionsDTO;
}

InstructionsDTO LobbyDeserializer::deserialize_start_game(bool *was_closed)
{
    std::vector<char> buffer;
    InstructionsDTO instructionsDTO(START,buffer);
    return instructionsDTO; 
}