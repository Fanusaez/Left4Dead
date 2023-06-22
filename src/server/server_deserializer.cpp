#include "server_deserializer.h"
#include "../common/instructions_type.h"
#include <exception>
#include <iostream>
#include <arpa/inet.h>

ServerDeserializer::ServerDeserializer(Socket *socket) : socket(socket) {}

InstructionsDTO* ServerDeserializer::obtener_instruccion(bool *was_closed, int32_t& player_id) {
    char code = 0;
    socket->recvall(&code, 1, was_closed);
    //Que pasa si se cierra el socket mientras espero la proxima instruccion?
    if (*was_closed){
        throw std::runtime_error("Se cerro el socket esperando una instruccion");
    }
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
        case GRENADE:
            return (deserialize_grenede(was_closed, player_id));
            break;
        case REVIVE:
            return (deserialize_revive(was_closed, player_id));
            break;
        }
}

CreateDTO* ServerDeserializer::deserialize_create(bool *was_closed, int32_t& player_id)
{
    uint8_t length = 0;
    socket->recvall(&length, 1, was_closed);
    std::vector<char> buffer(length);
    socket->recvall(buffer.data(), length, was_closed);
    CreateDTO* create_dto = new CreateDTO(player_id, std::string(buffer.begin(), buffer.end()));
    return create_dto;
}

JoinDTO* ServerDeserializer::deserialize_join(bool *was_closed, int32_t& player_id)
{
    int32_t game_code;
    socket->recvall(&game_code, sizeof(int32_t), was_closed);
    game_code = ntohl(game_code);
    JoinDTO* join_dto = new JoinDTO(player_id, game_code);
    return join_dto;
}

MoveDTO* ServerDeserializer::deserialize_move(bool *was_closed, int32_t& player_id) {
    char move_type; 
    socket->recvall(&move_type, 1, was_closed);
    MoveType cast_move_type = static_cast<MoveType>(move_type);
    MoveDTO* move_dto = new MoveDTO(player_id, cast_move_type);
    return move_dto;
}

InstructionsDTO* ServerDeserializer::deserialize_reloading(bool *was_closed, int32_t& player_id)
{
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, RELOAD);
    return instructionDTO;
}

InstructionsDTO* ServerDeserializer::deserialize_shooting(bool *was_closed, int32_t& player_id)
{
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, SHOOT);
    return instructionDTO;
}

GrenadeDTO* ServerDeserializer::deserialize_grenede(bool *was_closed, int32_t& player_id) {
    int8_t time;
    socket->recvall(&time, 1, was_closed);
    GrenadeDTO* instructionDTO = new GrenadeDTO(player_id, time);
    return instructionDTO;
}

InstructionsDTO* ServerDeserializer::deserialize_start(bool *was_closed, int32_t& player_id) {
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, START);
    return instructionDTO;
}

InstructionsDTO* ServerDeserializer::deserialize_revive(bool *was_closed, int32_t& player_id) {
    InstructionsDTO* instructionDTO = new InstructionsDTO(player_id, REVIVE);
    return instructionDTO;
}