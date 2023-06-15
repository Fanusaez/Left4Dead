#include "client_deserializer.h"
#include <iostream>
#include <arpa/inet.h>

ClientDeserializer::ClientDeserializer(Socket *socket) : socket(socket) {}

/*----------------------Game message--------------------*/

GameDTO ClientDeserializer::deserialize_game_dto(bool *was_closed)
{
    GameDTO game_dto;
    uint8_t soldiers_size;
    uint8_t zombies_size;
    int32_t player_id;
    int16_t id;
    int16_t health;
    int16_t position_x;
    int16_t position_y;
    int16_t bullets;
    char soldier_state; 
    char zobmie_state; 
    char soldier_type;
    char zombie_type; 
    bool facingLeft;
    socket->recvall(&soldiers_size, 1, was_closed);
    socket->recvall(&zombies_size, 1, was_closed);
    for (int i = 0; i < soldiers_size; i++)
    {   
        socket->recvall(&player_id, sizeof(int32_t), was_closed);
        socket->recvall(&id, sizeof(int16_t), was_closed);
        socket->recvall(&soldier_state, sizeof(char), was_closed);
        socket->recvall(&soldier_type, sizeof(char), was_closed);
        socket->recvall(&position_x, sizeof(int16_t), was_closed);
        socket->recvall(&position_y, sizeof(int16_t), was_closed);
        socket->recvall(&facingLeft, sizeof(bool), was_closed);
        socket->recvall(&bullets, sizeof(int16_t), was_closed);
        socket->recvall(&health, sizeof(int16_t), was_closed);
        game_dto.add_soldier(SoldierObjectDTO(ntohl(player_id), ntohs(id), ntohs(health),
                                    ntohs(position_x), ntohs(position_y), ntohs(bullets),
                                    static_cast<SoldierObjectState>(soldier_state),
                                    static_cast<SoldierType>(soldier_type),facingLeft));
    }
    for (int i = 0; i < zombies_size; i++)
    {
        socket->recvall(&id, sizeof(int16_t), was_closed);
        socket->recvall(&zobmie_state, sizeof(char), was_closed);
        socket->recvall(&zombie_type, sizeof(char), was_closed);
        socket->recvall(&position_x, sizeof(int16_t), was_closed);
        socket->recvall(&position_y, sizeof(int16_t), was_closed);
        socket->recvall(&facingLeft, sizeof(bool), was_closed);
        game_dto.add_zombie(ZombieObjectDTO(ntohs(id), ntohs(position_x), ntohs(position_y), 
        static_cast<ZombieObjectState>(zobmie_state),static_cast<ZombieType>(zombie_type),
        facingLeft));
    }
    return game_dto;
}
