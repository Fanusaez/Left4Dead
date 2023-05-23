#include "server_serializer.h"

#include <iostream>

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
    std::vector<GameObjectDTO> objects_game = game_dto.get_objects_game();
    buffer.push_back(uint8_t(objects_game.size()));
    for (const auto &obj : objects_game)
    {
        buffer.push_back(obj.state);

        buffer.push_back(obj.position_x & 0xFF);
        buffer.push_back((obj.position_x >> 8) & 0xFF);

        buffer.push_back(obj.position_y & 0xFF);
        buffer.push_back((obj.position_y >> 8) & 0xFF);
    }
    socket->sendall(buffer.data(), buffer.size(), was_closed);
}