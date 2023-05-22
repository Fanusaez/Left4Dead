#ifndef CLIENTSERIALIZER_H
#define CLIENTSERIALIZER_H

#include <vector>
#include <string>

#include "../common/game_mode.h"
#include "../common/soldier_type.h"
#include "../common/move.h"

class ClientSerializer{
private:

public:
    /*----------------------Lobby message--------------------*/

    std::vector<char> serialize_create_scenario(const std::string& scenario_name);

    std::vector<char> serialize_join_scenario(const int32_t& scenario_code);

    std::vector<char> serialize_game_mode(GameMode game_mode);

    std::vector<char> serialize_soldier(SoldierType soldier_type);

    std::vector<char> serialize_request_game_list();

    /*----------------------Game message--------------------*/

    std::vector<char> serialize_move(Move move);

    std::vector<char> serialize_reloading();

    std::vector<char> serialize_shooting();

    std::vector<char> serialize_throw_grenede(const int& time);
};
#endif
