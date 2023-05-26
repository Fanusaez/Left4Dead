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
        case CREATE:
            return (deserialize_create(was_closed, player_id));
            break;
        case JOIN:
            return (deserialize_join(was_closed, player_id));
            break;
        case MOVE:
            return (deserialize_move(was_closed, player_id));
            break;
        case RELOAD:
            return (deserialize_reloading(was_closed, player_id));
            break;
        case SHOOT:
            return (deserialize_shooting(was_closed, player_id));
            break;
        case GRANEDE:
            return (deserialize_grenede(was_closed, player_id));
            break;
        }
}

InstructionsDTO ServerDeserializer::deserialize_create(bool *was_closed, int* player_id)
{
    int longitud = 0;
    socket->recvall(&longitud, 1, was_closed);
    std::vector<char> buffer(longitud);
    socket->recvall(buffer.data(), longitud, was_closed);
    InstructionsDTO instructionDTO(player_id, CREATE,buffer);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_join(bool *was_closed, int* player_id)
{
    std::vector<char> buffer(4);
    socket->recvall(buffer.data(), 4, was_closed);
    InstructionsDTO instructionsDTO(player_id, JOIN,buffer);
    return instructionsDTO;
}

InstructionsDTO ServerDeserializer::deserialize_move(bool *was_closed, int* player_id)
{
    std::vector<char> bytes(1);
    socket->recvall(bytes.data(), 1, was_closed);
    InstructionsDTO instructionDTO(player_id, MOVE, bytes);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_reloading(bool *was_closed, int* player_id)
{
    InstructionsDTO instructionDTO(player_id, RELOAD);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_shooting(bool *was_closed, int* player_id)
{
    InstructionsDTO instructionDTO(player_id, SHOOT);
    return instructionDTO;
}

InstructionsDTO ServerDeserializer::deserialize_grenede(bool *was_closed, int* player_id)
{
    std::vector<char> bytes;
    socket->recvall(bytes.data(), 1, was_closed);
    InstructionsDTO instructionDTO(player_id, GRANEDE, bytes);
    return instructionDTO;
}