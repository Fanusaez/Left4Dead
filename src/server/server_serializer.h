#ifndef SERVERSERIALIZER_H
#define SERVERSERIALIZER_H

#include "../common/soldier_type.h"
#include "../common/game_mode.h"
#include "../common/game_dto.h"
#include "../common/socket.h"
#include "../common/move.h"

#include <vector>
#include <string>
class ServerSerializer
{
private:
    Socket *socket;

public:
    ServerSerializer(); //Solo para testing

    ServerSerializer(Socket *socket);

    std::vector<char> serialize_create_scenario(int32_t *scenario_code);

    std::vector<char> serialize_join_scenario(bool *join);

    std::vector<char> serialize_soldier_position(int16_t *pos_x, int16_t *pos_y);

    std::vector<char> serialize_soldier_ammo(int *ammo);

    std::vector<char> serialize_soldier_health(int *health);

    std::vector<char> serialize_game_stats(int *infected, int16_t *ammo, int16_t *time);

    std::vector<char> serialize_games_availables(int *games, std::vector<int> *codes, std::vector<int> *people);

    void send_game(GameDTO game_dto, bool *was_closed);
};
#endif
