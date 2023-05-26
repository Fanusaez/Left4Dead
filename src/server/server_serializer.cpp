#include "server_serializer.h"

#include <iostream>
#include <cstring>

ServerSerializer::ServerSerializer() {}

ServerSerializer::ServerSerializer(Socket *socket) : socket(socket)
{
}

std::vector<char> ServerSerializer::serialize_create_scenario(int32_t *scenario_code) {
    std::vector<char> buffer;
    buffer.push_back((*scenario_code >> 24) & 0xFF);
    buffer.push_back((*scenario_code >> 16) & 0xFF);
    buffer.push_back((*scenario_code >> 8) & 0xFF);
    buffer.push_back(*scenario_code & 0xFF);
    return buffer;
}

std::vector<char> ServerSerializer::serialize_join_scenario(bool *join){
    std::vector<char> buffer;
    if (*join)
        buffer.push_back(0x01);
    else
        buffer.push_back(0x00);

    return buffer;
}

std::vector<char> ServerSerializer::serialize_soldier_position(int16_t *pos_x, int16_t *pos_y)
{
    std::vector<char> buffer;
    buffer.push_back(0x01);

    buffer.push_back((*pos_x >> 8) & 0xFF);
    buffer.push_back(*pos_x & 0xFF);

    buffer.push_back((*pos_y >> 8) & 0xFF);
    buffer.push_back(*pos_y & 0xFF);

    return buffer;
}

std::vector<char> ServerSerializer::serialize_soldier_ammo(int *ammo)
{
    std::vector<char> buffer;
    buffer.push_back(0x02);

    buffer.push_back(0x01); // <msg lem>
    buffer.push_back(*ammo);

    return buffer;
}

std::vector<char> ServerSerializer::serialize_soldier_health(int *health)
{
    std::vector<char> buffer;
    buffer.push_back(0x03);

    buffer.push_back(0x01); // <msg lem>
    buffer.push_back(*health);

    return buffer;
}

std::vector<char> ServerSerializer::serialize_game_stats(int *infected, int16_t *ammo, int16_t *time)
{
    std::vector<char> buffer;

    buffer.push_back(0x04);
    buffer.push_back(*infected);

    buffer.push_back((*ammo >> 8) & 0xFF);
    buffer.push_back(*ammo & 0xFF);

    buffer.push_back((*time >> 8) & 0xFF);
    buffer.push_back(*time & 0xFF);

    return buffer;
}

std::vector<char> ServerSerializer::serialize_games_availables(int *games, std::vector<int> *codes, std::vector<int> *people){
    std::vector<char> buffer;

    buffer.push_back(*games);
    for(int i = 0; i < *games; i++){
        buffer.push_back(codes->at(i));
        buffer.push_back(people->at(i));
    }
    return buffer;
}

void ServerSerializer::send_game(GameDTO game_dto, bool *was_closed)
{
    std::vector<char> buffer;
    std::vector<SoldierObjectDTO> soldiers = game_dto.get_soldiers();
    std::vector<ZombieObjectDTO> zombies = game_dto.get_zombies();
    buffer.push_back(soldiers.size());
    buffer.push_back(zombies.size());
    for (const auto &obj : soldiers) {
        buffer.push_back(obj.id);

        buffer.push_back(obj.state);
        buffer.push_back(obj.soldier_type);

        unsigned char const * p = reinterpret_cast<unsigned char const *>(&obj.position_x);
        buffer.insert(buffer.end(), p, p + 4);

        p = reinterpret_cast<unsigned char const *>(&obj.position_y);
        buffer.insert(buffer.end(), p, p + 4);

    }

    for (const auto &obj : zombies) {
        buffer.push_back(obj.id);
        buffer.push_back(obj.state);

        unsigned char const * p = reinterpret_cast<unsigned char const *>(&obj.position_x);
        buffer.insert(buffer.end(), p, p + 4);

        p = reinterpret_cast<unsigned char const *>(&obj.position_y);
        buffer.insert(buffer.end(), p, p + 4);

    }
    int sz = socket->sendall(buffer.data(), buffer.size(), was_closed);
    //std::cout<<"Envio n bytes: "<<sz<<std::endl;
}