#include "client_deserializer.h"
#include <iostream>
ClientDeserializer::ClientDeserializer(Socket *socket) : socket(socket) {}

/*----------------------Game message--------------------*/

GameDTO ClientDeserializer::deserialize_game_dto(bool *was_closed)
{
    GameDTO game_dto;
    int8_t soldiers_size;
    int8_t zombies_size;
    int16_t player_id;
    int16_t id;
    int16_t health;
    int16_t position_x;
    int16_t position_y;
    int16_t bullets;
    char soldier_state; 
    char zobmie_state; 
    char soldier_type;
    bool facingLeft;
    socket->recvall(&soldiers_size, 1, was_closed);
    socket->recvall(&zombies_size, 1, was_closed);
    for (int i = 0; i < int(soldiers_size); i++)
    {   
        socket->recvall(&player_id, 4, was_closed);
        socket->recvall(&id, 2, was_closed);
        socket->recvall(&soldier_state, 1, was_closed);
        socket->recvall(&soldier_type, 1, was_closed);
        socket->recvall(&position_x, 2, was_closed);
        socket->recvall(&position_y, 2, was_closed);
        socket->recvall(&facingLeft, 1, was_closed);
        socket->recvall(&bullets, 2, was_closed);
        socket->recvall(&health, 2, was_closed);
        game_dto.add_soldier(SoldierObjectDTO(player_id, id, health, position_x, position_y, bullets,
            static_cast<SoldierObjectState>(soldier_state), static_cast<SoldierType>(soldier_type),facingLeft));
        //std::cout<<"P_id: "<<player_id<<" Id: "<<id<<" Health: "<<health<<" X: "<<position_x<<" Y: "<<position_y<<" bullets: "<<bullets<<std::endl;s
    }
    for (int i = 0; i < int(zombies_size); i++)
    {
        socket->recvall(&id, 1, was_closed);
        socket->recvall(&zobmie_state, 1, was_closed);
        socket->recvall(&position_x, 4, was_closed);
        socket->recvall(&position_y, 4, was_closed);
        socket->recvall(&facingLeft, 1, was_closed);
        game_dto.add_zombie(ZombieObjectDTO(id, position_x, position_y, static_cast<ZombieObjectState>(zobmie_state),facingLeft));
    }
    return game_dto;
}