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
    uint8_t grenades_size;
    int32_t player_id;
    int16_t id;
    int16_t health;
    int16_t position_x;
    int16_t position_y;
    int16_t bullets;
    int16_t time_explosive_grenade;
    int16_t time_smoke_grenade;
    char soldier_state; 
    char zobmie_state; 
    char soldier_type;
    char zombie_type; 
    char grenade_type; 
    bool facingLeft;
    bool end_game;
    socket->recvall(&soldiers_size, 1, was_closed);
    socket->recvall(&zombies_size, 1, was_closed);
    socket->recvall(&grenades_size, 1, was_closed);
    socket->recvall(&end_game, 1, was_closed);
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
        socket->recvall(&time_explosive_grenade, sizeof(int16_t), was_closed);
        socket->recvall(&time_smoke_grenade, sizeof(int16_t), was_closed);
        game_dto.add_soldier(SoldierObjectDTO(ntohl(player_id), ntohs(id), ntohs(health),
                                    ntohs(position_x), ntohs(position_y), ntohs(bullets), 
                                    ntohs(time_explosive_grenade), ntohs(time_smoke_grenade),
                                    static_cast<SoldierObjectState>(soldier_state),
                                    static_cast<SoldierType>(soldier_type),facingLeft));
    }
    for (int i = 0; i < zombies_size; i++)
    {
        socket->recvall(&id, sizeof(int16_t), was_closed);
        socket->recvall(&health, sizeof(int16_t), was_closed);
        socket->recvall(&zobmie_state, sizeof(char), was_closed);
        socket->recvall(&zombie_type, sizeof(char), was_closed);
        socket->recvall(&position_x, sizeof(int16_t), was_closed);
        socket->recvall(&position_y, sizeof(int16_t), was_closed);
        socket->recvall(&facingLeft, sizeof(bool), was_closed);
        game_dto.add_zombie(ZombieObjectDTO(ntohs(id), ntohs(health), ntohs(position_x), ntohs(position_y), 
        static_cast<ZombieObjectState>(zobmie_state),static_cast<ZombieType>(zombie_type),
        facingLeft));
    }
    for (int i = 0; i < grenades_size; i++)
    {
        socket->recvall(&id, sizeof(int16_t), was_closed);
        socket->recvall(&position_x, sizeof(int16_t), was_closed);
        socket->recvall(&position_y, sizeof(int16_t), was_closed);
        socket->recvall(&grenade_type, sizeof(char), was_closed);
        game_dto.add_element(GrenadeObjectDTO(ntohs(id), ntohs(position_x), ntohs(position_y), 
        static_cast<GrenadeType>(grenade_type)));
    }

    int16_t total_bullets;
    int16_t total_dead_zombies;

    socket->recvall(&total_bullets, sizeof(int16_t), was_closed);
    socket->recvall(&total_dead_zombies, sizeof(int16_t), was_closed);

    game_dto.add_game_stats(GameStats(ntohs(total_bullets),ntohs(total_dead_zombies)));

    game_dto.set_end_game(end_game);
    
    return game_dto;
}
