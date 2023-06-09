#include "server_deserializer.h"
#include "../common/instructions_type.h"

#include <iostream>

ServerDeserializer::ServerDeserializer(Socket *socket) : socket(socket) {}

InstructionsDTO* ServerDeserializer::obtener_instruccion(bool *was_closed, int* player_id)
{
    char code = 0;
    socket->recvall(&code, 1, was_closed);
/*     if (*was_closed){
        InstructionsDTO instruction;
        return instruction;
    } */
    InstructionsType instruction = static_cast<InstructionsType>(code);
    switch (instruction) {
        case CREATE:
            return (deserialize_create(was_closed, player_id));
            break;
       case JOIN:
            return (deserialize_join(was_closed, player_id));
            break;
        case START:
            return (deserialize_start(was_closed, player_id));
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
            //return (deserialize_grenede(was_closed, player_id));
            break;
        }

}

CreateDTO* ServerDeserializer::deserialize_create(bool *was_closed, int* player_id)
{
    int longitud = 0;
    socket->recvall(&longitud, 1, was_closed);
    std::vector<char> buffer(longitud);
    socket->recvall(buffer.data(), longitud, was_closed);
    CreateDTO* create_dto = new CreateDTO(player_id, std::string(buffer.begin(), buffer.end()));
    return create_dto;
}

JoinDTO* ServerDeserializer::deserialize_join(bool *was_closed, int* player_id)
{
    int32_t game_code;
    socket->recvall(&game_code, 4, was_closed);
    JoinDTO* join_dto = new JoinDTO(player_id, game_code);
    return join_dto;
}

MoveDTO* ServerDeserializer::deserialize_move(bool *was_closed, int* player_id)
{
    MoveType move_type;
    socket->recvall(&move_type, 1, was_closed);
    MoveDTO* move_dto = new MoveDTO(player_id, move_type);
    return move_dto;
}

InstructionsDTO* ServerDeserializer::deserialize_reloading(bool *was_closed, int* player_id)
{
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, RELOAD);
    return instructionDTO;
}

InstructionsDTO* ServerDeserializer::deserialize_shooting(bool *was_closed, int* player_id)
{
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, SHOOT);
    return instructionDTO;
}

/* InstructionsDTO* ServerDeserializer::deserialize_grenede(bool *was_closed, int* player_id)
{
    std::vector<char> bytes;
    socket->recvall(bytes.data(), 1, was_closed);
    InstructionsDTO instructionDTO(player_id, GRANEDE, bytes);
    return instructionDTO;
} */

InstructionsDTO* ServerDeserializer::deserialize_start(bool *was_closed, int* player_id)
{
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, START);
    return instructionDTO;
}
