#include "server_deserializer.h"
#include "../common/instructions.h"

#include <iostream>

ServerDeserializer::ServerDeserializer(Socket *socket) : socket(socket) {}

InstructionsDTO ServerDeserializer::obtener_instruccion(bool *was_closed, int* player_id)
{
    char code = 0;
    socket->recvall(&code, 1, was_closed);
    Instructions instruction = static_cast<Instructions>(code);
    switch (instruction) {
        case MOVE:
            return (deserialize_move(was_closed, player_id));
            break;
        case RELOAD:
            return (deserialize_reloading(was_closed));
            break;
        case SHOOT:
            return (deserialize_shooting(was_closed));
            break;
        case GRANEDE:
            return (deserialize_grenede(was_closed));
            break;
        }
}

std::string ServerDeserializer::deserialize_create(bool *was_closed)
{
    int longitud = 0;
    socket->recvall(&longitud, 1, was_closed);

    std::vector<char> buffer(longitud);
    socket->recvall(buffer.data(), longitud, was_closed);
    std::string game_name(buffer.begin(), buffer.end());
    return game_name;
}

int32_t ServerDeserializer::deserialize_join(bool *was_closed)
{
    int32_t code = 0;
    socket->recvall(&code, 4, was_closed);
    return code;
}

InstructionsDTO ServerDeserializer::deserialize_move(bool *was_closed, int* player_id)
{
    std::vector<char> bytes(1);
    socket->recvall(bytes.data(), 1, was_closed);
    InstructionsDTO instructionDTO(player_id, MOVE, bytes);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_reloading(bool *was_closed)
{
    InstructionsDTO instructionDTO(RELOAD);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_shooting(bool *was_closed)
{
    InstructionsDTO instructionDTO(SHOOT);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_grenede(bool *was_closed)
{
    std::vector<char> bytes;
    socket->recvall(bytes.data(), 1, was_closed);
    InstructionsDTO instructionDTO(GRANEDE, bytes);
    return instructionDTO;
}