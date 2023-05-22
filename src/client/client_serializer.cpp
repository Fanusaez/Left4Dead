#include "client_serializer.h"
#include "../common/instructions.h"

std::vector<char> ClientSerializer::serialize_create_scenario(const std::string& scenario_name){
    std::vector<char> buffer;
    buffer.push_back(CREATE); //Capaz enum con todas las instrucciones/mensajes a mandar
    buffer.push_back(scenario_name.length());
    buffer.insert(buffer.end(), scenario_name.begin(), scenario_name.end());
    return buffer;
}

std::vector<char> ClientSerializer::serialize_join_scenario(const int32_t& scenario_code)
{
    std::vector<char> buffer;
    buffer.push_back(JOIN);
    buffer.push_back((scenario_code >> 24) & 0xFF);
    buffer.push_back((scenario_code >> 16) & 0xFF);
    buffer.push_back((scenario_code >> 8) & 0xFF);
    buffer.push_back(scenario_code & 0xFF);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_game_mode(GameMode game_mode)
{
    std::vector<char> buffer;
    buffer.push_back(GAME_MODE);
    if (game_mode == CLEAR_THE_ZONE || game_mode == SURVIVAL)
        buffer.push_back(game_mode);
    else
        // Throw error?
    return buffer;
}

std::vector<char> ClientSerializer::serialize_soldier(SoldierType soldier_type)
{
    std::vector<char> buffer;
    buffer.push_back(SOLDIER_TYPE);
    if (soldier_type == IDF || soldier_type == P90 || soldier_type == SCOUT)
        buffer.push_back(soldier_type);
    else
        // Throw error?
    return buffer;
}

std::vector<char> ClientSerializer::serialize_request_game_list(){
    std::vector<char> buffer;
    buffer.push_back(GAME_LIST);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_move(Move move)
{
    std::vector<char> buffer;
    buffer.push_back(MOVE);
    buffer.push_back(move);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_reloading()
{
    std::vector<char> buffer;
    buffer.push_back(RELOAD);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_shooting(){
    std::vector<char> buffer;
    buffer.push_back(SHOOT);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_throw_grenede(const int& time){
    std::vector<char> buffer;
    buffer.push_back(GRANEDE);
    buffer.push_back(time);
    return buffer;
}