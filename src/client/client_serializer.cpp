#include "client_serializer.h"
#include "../common/instructions_type.h"
#include <iostream>

std::vector<char> ClientSerializer::serialize_start_playing(){
    std::vector<char> buffer;
    buffer.push_back(START);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_move(const MoveType move) {
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

std::vector<char> ClientSerializer::serialize_throw_explosive_grenede(const int8_t& time){
    std::vector<char> buffer;
    buffer.push_back(THROW_EXPLOSIVE_GRENADE);
    buffer.push_back(time);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_throw_smoke_grenede(const int8_t& time){
    std::vector<char> buffer;
    buffer.push_back(THROW_SMOKE_GRENADE);
    buffer.push_back(time);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_call_air_strike() {
    std::vector<char> buffer;
    buffer.push_back(CALL_AIR_STRIKE);
    return buffer;
}

std::vector<char> ClientSerializer::serialize_revive_soldier(){
    std::vector<char> buffer;
    buffer.push_back(REVIVE);
    return buffer;
}
