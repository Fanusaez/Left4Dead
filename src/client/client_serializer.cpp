#include "client_serializer.h"
#include "../common/instructions.h"
#include <iostream>

std::vector<char> ClientSerializer::serialize_start_playing(){
    std::vector<char> buffer;
    buffer.push_back(START);
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