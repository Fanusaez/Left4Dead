#include "server_serializer.h"

#include <iostream>

std::vector<char> ServerSerializer::translate_create_scenario(int32_t *scenario_code)
{
    std::vector<char> buffer;
    buffer.push_back((*scenario_code >> 24) & 0xFF);
    buffer.push_back((*scenario_code >> 16) & 0xFF);
    buffer.push_back((*scenario_code >> 8) & 0xFF);
    buffer.push_back(*scenario_code & 0xFF);
    return buffer;
}

std::vector<char> ServerSerializer::translate_join_scenario(bool *join){
    std::vector<char> buffer;
    if (*join)
        buffer.push_back(0x01);
    else
        buffer.push_back(0x00);

    return buffer;
}

std::vector<char> ServerSerializer::translate_soldier_position(int16_t *pos_x, int16_t *pos_y)
{
    std::vector<char> buffer;
    buffer.push_back(0x01);

    buffer.push_back((*pos_x >> 8) & 0xFF);
    buffer.push_back(*pos_x & 0xFF);

    buffer.push_back((*pos_y >> 8) & 0xFF);
    buffer.push_back(*pos_y & 0xFF);

    return buffer;
}

std::vector<char> ServerSerializer::translate_soldier_ammo(int *ammo)
{
    std::vector<char> buffer;
    buffer.push_back(0x02);

    buffer.push_back(0x01); // <msg lem>
    buffer.push_back(*ammo);

    return buffer;
}

std::vector<char> ServerSerializer::translate_soldier_health(int *health)
{
    std::vector<char> buffer;
    buffer.push_back(0x03);

    buffer.push_back(0x01); // <msg lem>
    buffer.push_back(*health);

    return buffer;
}

std::vector<char> ServerSerializer::translate_game_stats(int *infected, int16_t *ammo, int16_t *time)
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

std::vector<char> ServerSerializer::translate_games_availables(int *games, std::vector<int> *codes, std::vector<int> *people){
    std::vector<char> buffer;

    buffer.push_back(*games);
    for(int i = 0; i < *games; i++){
        buffer.push_back(codes->at(i));
        buffer.push_back(people->at(i));
    }
    return buffer;
}
