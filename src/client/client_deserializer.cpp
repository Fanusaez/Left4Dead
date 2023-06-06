#include "client_deserializer.h"
#include <iostream>
ClientDeserializer::ClientDeserializer(Socket *socket) : socket(socket) {}

/*----------------------Game message--------------------*/

GameDTO ClientDeserializer::deserialize_game_dto(bool *was_closed)
{
    GameDTO game_dto;
    char soldiers_size;
    char zombies_size;
    int id;
    int position_x;
    int position_y;
    char soldier_state; 
    char zobmie_state; 
    char soldier_type;
    bool facingLeft;
    socket->recvall(&soldiers_size, 1, was_closed);
    socket->recvall(&zombies_size, 1, was_closed);
    for (int i = 0; i < int(soldiers_size); i++)
    {   
        socket->recvall(&id, 1, was_closed);
        socket->recvall(&soldier_state, 1, was_closed);
        socket->recvall(&soldier_type, 1, was_closed);
        socket->recvall(&position_x, 4, was_closed);
        socket->recvall(&position_y, 4, was_closed);
        socket->recvall(&facingLeft, 1, was_closed);
        game_dto.add_soldier(SoldierObjectDTO(id, position_x, position_y, static_cast<SoldierObjectState>(soldier_state), static_cast<SoldierType>(soldier_type),facingLeft));
        //std::cout<<position_x<<","<<position_y<<std::endl;
    }
    for (int i = 0; i < int(zombies_size); i++)
    {
        socket->recvall(&id, 1, was_closed);
        socket->recvall(&zobmie_state, 1, was_closed);
        socket->recvall(&position_x, 4, was_closed);
        socket->recvall(&position_y, 4, was_closed);
        game_dto.add_zombie(ZombieObjectDTO(id, position_x, position_y, static_cast<ZombieObjectState>(zobmie_state)));
    }
    return game_dto;
}