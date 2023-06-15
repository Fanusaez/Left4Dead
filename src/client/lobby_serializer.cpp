#include "lobby_serializer.h"
#include "../common/instructions_type.h"
#include <iostream>
#include <arpa/inet.h>

std::vector<char> LobbySerializer::serialize_create_scenario(const std::string& scenario_name) {
    std::vector<char> buffer;
    buffer.push_back(CREATE);
    uint8_t length = scenario_name.length();
    buffer.push_back(length);
    buffer.insert(buffer.end(), scenario_name.begin(), scenario_name.end());
    return buffer;
}

std::vector<char> LobbySerializer::serialize_join_scenario(const int32_t& scenario_code) {
    std::vector<char> buffer;
    buffer.push_back(JOIN);
    int32_t transformed_scenario_code = htonl(scenario_code);
    unsigned char const* p = reinterpret_cast<unsigned char const *>(&transformed_scenario_code);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> LobbySerializer::serialize_game_mode(const GameMode game_mode) {
    std::vector<char> buffer;
    buffer.push_back(GAME_MODE);
    if (game_mode == CLEAR_THE_ZONE || game_mode == SURVIVAL)
        buffer.push_back(game_mode);
    else
        // Throw error?
    return buffer;
}

std::vector<char> LobbySerializer::serialize_soldier(const SoldierType soldier_type) {
    std::vector<char> buffer;
    buffer.push_back(SOLDIER_TYPE);
    if (soldier_type == IDF || soldier_type == P90 || soldier_type == SCOUT)
        buffer.push_back(soldier_type);
    else
        // Throw error?
    return buffer;
}

std::vector<char> LobbySerializer::serialize_request_game_list() {
    std::vector<char> buffer;
    buffer.push_back(GAME_LIST);
    return buffer;
}

std::vector<char> LobbySerializer::serialize_start_playing() {
    std::vector<char> buffer;
    buffer.push_back(START);
    return buffer;
}

