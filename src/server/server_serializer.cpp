#include "server_serializer.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>


ServerSerializer::ServerSerializer() {}

ServerSerializer::ServerSerializer(Socket *socket) : socket(socket){}

void ServerSerializer::send_create_scenario(const int32_t &scenario_code, bool *was_closed) {
    std::vector<char> buffer = serialize_create_scenario(scenario_code);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::send_error_create(bool *was_closed) {
    std::vector<char> buffer = serialize_error_create();
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::send_join_scenario(const bool &join, bool *was_closed){
    std::vector<char> buffer = serialize_join_scenario(join);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::send_start_game(const bool &start, bool *was_closed) {
    std::vector<char> buffer = serialize_start_game(start);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

void ServerSerializer::send_player_id(const int32_t& player_id, bool* was_closed) {
    std::vector<char> buffer = serialize_player_id(player_id);
    socket->sendall(buffer.data(), buffer.size(), was_closed);    
}

void ServerSerializer::send_game(const GameDTO game_dto, bool *was_closed) {
    std::vector<char> buffer = serialize_game(game_dto);
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}

std::vector<char> ServerSerializer::serialize_create_scenario(const int32_t &scenario_code) {
    std::vector<char> buffer;
    buffer.push_back(CREATE);
    int32_t transformed_scenario_code = htonl(scenario_code);
    unsigned char const * p = reinterpret_cast<unsigned char const *>(&transformed_scenario_code);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServerSerializer::serialize_error_create() {
    std::vector<char> buffer;
    buffer.push_back(CREATE);
    buffer.push_back(0x01);
    return buffer;
}

std::vector<char> ServerSerializer::serialize_join_scenario(const bool &join) {
    std::vector<char> buffer;
    buffer.push_back(JOIN);
    buffer.push_back(join);
    return buffer;
}

std::vector<char> ServerSerializer::serialize_start_game(const bool &start) {
    std::vector<char> buffer;
    buffer.push_back(START);
    buffer.push_back(start);
    return buffer;
}

std::vector<char> ServerSerializer::serialize_player_id(const int32_t& player_id) {
    std::vector<char> buffer;
    int32_t transformed_player_id = htonl(player_id);
    unsigned char const * p = reinterpret_cast<unsigned char const *>(&transformed_player_id);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> ServerSerializer::serialize_game(GameDTO game_dto) {
    std::vector<SoldierObjectDTO> soldiers = game_dto.get_soldiers();
    std::vector<ZombieObjectDTO> zombies = game_dto.get_zombies();

    uint8_t num_soldiers = soldiers.size();
    uint8_t num_zombies = zombies.size();

    std::vector<char> buffer;
    buffer.reserve(2 + (sizeof(SoldierObjectDTO) * num_soldiers) + (sizeof(ZombieObjectDTO) * num_zombies));
    buffer.push_back(static_cast<char>(num_soldiers));
    buffer.push_back(static_cast<char>(num_zombies));
    
    for (const auto &obj : soldiers) {
        int32_t transformed_player_id = htonl(obj.player_id);
        unsigned char const * p = reinterpret_cast<unsigned char const *>(&transformed_player_id);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        int16_t transformed_id = htons(obj.id);
        p = reinterpret_cast<unsigned char const *>(&transformed_id);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));


        buffer.push_back(obj.state);
        buffer.push_back(obj.soldier_type);

        int16_t transformed_position_x = htons(obj.position_x);
        p = reinterpret_cast<unsigned char const *>(&transformed_position_x);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        int16_t transformed_position_y = htons(obj.position_y);
        p = reinterpret_cast<unsigned char const *>(&transformed_position_y);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.facing_left);
        
        int16_t transformed_bullets = htons(obj.bullets);
        p = reinterpret_cast<unsigned char const *>(&transformed_bullets);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        int16_t transformed_health = htons(obj.health);
        p = reinterpret_cast<unsigned char const *>(&transformed_health);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));
    }

    for (const auto &obj : zombies) {
        int16_t transformed_id = htons(obj.id);
        unsigned char const * p = reinterpret_cast<unsigned char const *>(&transformed_id);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.state);
        buffer.push_back(obj.zombie_type);

        int16_t transformed_position_x = htons(obj.position_x);
        p = reinterpret_cast<unsigned char const *>(&transformed_position_x);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        int16_t transformed_position_y = htons(obj.position_y);
        p = reinterpret_cast<unsigned char const *>(&transformed_position_y);
        buffer.insert(buffer.end(), p, p + sizeof(int16_t));

        buffer.push_back(obj.facing_left);
    }
    return buffer;
}