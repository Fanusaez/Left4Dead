#include "server_translator.h"

#include <iostream>

std::vector<char> ServerTranslator::translate_create_scenario(int32_t *scenario_code)
{
    std::vector<char> buffer;
    buffer.push_back((*scenario_code >> 24) & 0xFF);
    buffer.push_back((*scenario_code >> 16) & 0xFF);
    buffer.push_back((*scenario_code >> 8) & 0xFF);
    buffer.push_back(*scenario_code & 0xFF);
    return buffer;
}

std::vector<char> ServerTranslator::translate_join_scenario(bool *join){
    std::vector<char> buffer;
    if (*join)
        buffer.push_back(0x01);
    else
        buffer.push_back(0x00);

    return buffer;
}

std::vector<char> ServerTranslator::translate_soldier_position(int16_t *pos_x, int16_t *pos_y)
{
    std::vector<char> buffer;
    buffer.push_back(0x01);

    buffer.push_back((*pos_x >> 8) & 0xFF);
    buffer.push_back(*pos_x & 0xFF);

    buffer.push_back((*pos_y >> 8) & 0xFF);
    buffer.push_back(*pos_y & 0xFF);

    return buffer;
}

std::vector<char> ServerTranslator::translate_soldier_ammo(int *ammo)
{
    std::vector<char> buffer;
    buffer.push_back(0x02);

    buffer.push_back(0x01); // <msg lem>
    buffer.push_back(*ammo);

    return buffer;
}

std::vector<char> ServerTranslator::translate_soldier_health(int *health)
{
    std::vector<char> buffer;
    buffer.push_back(0x03);

    buffer.push_back(0x01); // <msg lem>
    buffer.push_back(*health);

    return buffer;
}

std::vector<char> ServerTranslator::translate_game_stats(int *infected,int *ammo,int *time)
{
    std::vector<char> buffer;
    buffer.push_back(0x04);
    buffer.push_back(*infected);
    buffer.push_back(*ammo);
    buffer.push_back(*time);
}