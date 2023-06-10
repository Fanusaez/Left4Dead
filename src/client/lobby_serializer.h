#ifndef LOBBYSERIALIZER_H
#define LOBBYSERIALIZER_H

#include <vector>
#include <string>

#include "../common/game_mode.h"
#include "../common/soldier_type.h"
#include "../common/move_type.h"

class LobbySerializer{
private:
public:
    /*----------------------Lobby message--------------------*/

    std::vector<char> serialize_create_scenario(const std::string& scenario_name);

    std::vector<char> serialize_join_scenario(const int32_t& scenario_code);

    std::vector<char> serialize_game_mode(GameMode game_mode);

    std::vector<char> serialize_soldier(SoldierType soldier_type);

    std::vector<char> serialize_request_game_list();

    std::vector<char> serialize_start_playing();
};
#endif
