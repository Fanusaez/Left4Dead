#include "lobby_serializer.h"
#include "../common/instructions_type.h"
#include <iostream>
#include <arpa/inet.h>

std::vector<char> LobbySerializer::serialize_create_scenario(const std::string& scenario_name, const GameMode& game_mode, const int8_t& game_players) {
    std::vector<char> buffer;
    buffer.push_back(CREATE);
    uint8_t length = scenario_name.length();
    buffer.push_back(length);
    buffer.insert(buffer.end(), scenario_name.begin(), scenario_name.end());
    buffer.push_back(game_mode);
    buffer.push_back(game_players);
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

std::vector<char> LobbySerializer::serialize_soldier(const SoldierType& soldier_type) {
    std::vector<char> buffer;
    buffer.push_back(SOLDIER_TYPE);
    buffer.push_back(soldier_type);
    return buffer;
}

std::vector<char> LobbySerializer::serialize_start_playing() {
    std::vector<char> buffer;
    buffer.push_back(START);
    return buffer;
}

