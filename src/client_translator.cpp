#include "client_translator.h"

std::vector<char> ClientTranslator::translate_create_scenario(std::string *scenario_name){
    std::vector<char> buffer;
    buffer.push_back(0x01); //Capaz enum con todas las instrucciones/mensajes a mandar
    buffer.push_back(scenario_name->length());
    buffer.insert(buffer.end(), scenario_name->begin(), scenario_name->end());
    return buffer;
}

std::vector<char> ClientTranslator::translate_join_scenario(int32_t *scenario_code)
{
    std::vector<char> buffer;
    buffer.push_back(0x02);
    buffer.push_back(sizeof(int32_t));
    buffer.push_back((*scenario_code >> 24) & 0xFF);
    buffer.push_back((*scenario_code >> 16) & 0xFF);
    buffer.push_back((*scenario_code >> 8) & 0xFF);
    buffer.push_back(*scenario_code & 0xFF);
    return buffer;
}

std::vector<char> ClientTranslator::translate_game_mode(GameMode *game_mode)
{
    std::vector<char> buffer;
    buffer.push_back(0x03);
    buffer.push_back(0x01);
    if (*game_mode == CLEAR_THE_ZONE || *game_mode == SURVIVAL)
        buffer.push_back(*game_mode);
    else
        // Throw error?
    return buffer;
}

std::vector<char> ClientTranslator::translate_soldier(SoldierType *soldier_type)
{
    std::vector<char> buffer;
    buffer.push_back(0x04);
    buffer.push_back(0x01);
    if (*soldier_type == IDF || *soldier_type == P90 || *soldier_type == SCOUT)
        buffer.push_back(*soldier_type);
    else
        // Throw error?
    return buffer;
}

std::vector<char> ClientTranslator::translate_move(Move *move)
{
    std::vector<char> buffer;
    buffer.push_back(0x06);
    return buffer;
}