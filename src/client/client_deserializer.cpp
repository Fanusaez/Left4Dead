#include "client_deserializer.h"

ClientDeserializer::ClientDeserializer(Socket *socket) : socket(socket) {}

Instructions ClientDeserializer::obtener_instruccion(bool *was_closed)
{
    char code = 0;
    socket->recvall(&code, 1, was_closed);
    return static_cast<Instructions>(code);
}

/*----------------------Lobby message--------------------*/

int32_t ClientDeserializer::deserialize_create_scenario(bool *was_closed)
{
    int32_t game_code;
    socket->recvall(&game_code,4,was_closed);
    return game_code;
}

bool ClientDeserializer::deserialize_join_scenario(bool *was_closed)
{
    bool status_join;
}

/*----------------------Game message--------------------*/

GameDTO ClientDeserializer::deserialize_game_dto(bool *was_closed)
{
    GameDTO game_dto;
    int size_game_dto;
    socket->recvall(&size_game_dto, 1, was_closed);
    uint16_t position_x;   // Coordenada X de la posición
    uint16_t position_y;   // Coordenada Y de la posición
    GameObjectState state; // Estado del objeto
    for (int i = 0; i < size_game_dto; i++)
    {
        socket->recvall(&state, 1, &was_closed);
        socket->recvall(&position_x, 2, &was_closed);
        socket->recvall(&position_y, 2, &was_closed);
        game_dto.add_object(GameObjectDTO(1, position_x, position_y, state));
    }
}