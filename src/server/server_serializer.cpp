#include "server_serializer.h"

#include <iostream>
#include <cstring>

ServerSerializer::ServerSerializer() {}

ServerSerializer::ServerSerializer(Socket *socket) : socket(socket){}

void ServerSerializer::serialize_create_scenario(int32_t &scenario_code, bool *was_closed) {
    std::vector<char> buffer;
    buffer.push_back(CREATE);
    unsigned char const * p = reinterpret_cast<unsigned char const *>(&scenario_code);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::send_error_create(bool *was_closed){
    std::vector<char> buffer;
    buffer.push_back(CREATE);
    buffer.push_back(0x01);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::serialize_join_scenario(const bool &join, bool *was_closed){
    std::vector<char> buffer;
    buffer.push_back(JOIN);
    buffer.push_back(join);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::serialize_start_game(bool *was_closed) {
    std::vector<char> buffer;
    buffer.push_back(START);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::send_player_id(int& player_id, bool* was_closed) {
    std::vector<char> buffer;
    unsigned char const * p = reinterpret_cast<unsigned char const *>(&player_id);
    buffer.insert(buffer.end(), p, p + sizeof(int));
    socket->sendall(buffer.data(), buffer.size(), was_closed);    
}

/* std::vector<char> ServerSerializer::serialize_games_availables(const std::vector<Game*> &games){
    std::vector<char> buffer;

    std::mutex m;
    m.lock();
    buffer.push_back(games.size());
    for (auto &game: games){
        buffer.push_back(game->get_game_code());
        buffer.push_back(game->get_players());
    }
    return buffer;
} */

void ServerSerializer::send_game(GameDTO game_dto, bool *was_closed)
{
    std::vector<SoldierObjectDTO> soldiers = game_dto.get_soldiers();
    std::vector<ZombieObjectDTO> zombies = game_dto.get_zombies();

    size_t num_soldiers = soldiers.size();
    size_t num_zombies = zombies.size();

    std::vector<char> buffer;
    buffer.reserve(2 + (sizeof(SoldierObjectDTO) * num_soldiers) + (sizeof(ZombieObjectDTO) * num_zombies));
    buffer.push_back(static_cast<char>(num_soldiers));
    buffer.push_back(static_cast<char>(num_zombies));
    
    for (const auto &obj : soldiers) {
        unsigned char const * p = reinterpret_cast<unsigned char const *>(&obj.player_id);
        buffer.insert(buffer.end(), p, p + sizeof(int));

        p = reinterpret_cast<unsigned char const *>(&obj.id);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.state);
        buffer.push_back(obj.soldier_type);

        p = reinterpret_cast<unsigned char const *>(&obj.position_x);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        p = reinterpret_cast<unsigned char const *>(&obj.position_y);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.facing_left);
        
        p = reinterpret_cast<unsigned char const *>(&obj.bullets);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        p = reinterpret_cast<unsigned char const *>(&obj.health);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));
    }

    for (const auto &obj : zombies) {
        unsigned char const *p = reinterpret_cast<unsigned char const *>(&obj.id);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.state);
        buffer.push_back(obj.zombie_type);

        p = reinterpret_cast<unsigned char const *>(&obj.position_x);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        p = reinterpret_cast<unsigned char const *>(&obj.position_y);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.facing_left);
    }
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}
