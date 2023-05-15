#ifndef SERVERSERIALIZER_H
#define SERVERSERIALIZER_H

#include <vector>
#include <string>

#include "../src/game_mode.h"
#include "../src/soldier_type.h"
#include "../src/move.h"

class ServerSerializer
{
private:

public:
    std::vector<char> translate_create_scenario(int32_t *scenario_code);

    std::vector<char> translate_join_scenario(bool *join);

    std::vector<char> translate_soldier_position(int16_t *pos_x, int16_t *pos_y);

    std::vector<char> translate_soldier_ammo(int *ammo);

    std::vector<char> translate_soldier_health(int *health);

    std::vector<char> translate_game_stats(int *infected, int16_t *ammo, int16_t *time);

    std::vector<char> translate_games_availables(int *games, std::vector<int> *codes, std::vector<int> *people);
};
#endif
