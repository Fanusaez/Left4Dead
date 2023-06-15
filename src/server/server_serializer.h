#ifndef SERVERSERIALIZER_H
#define SERVERSERIALIZER_H

#include "../common/soldier_type.h"
#include "../common/game_mode.h"
#include "../common/game_dto.h"
#include "../common/socket.h"
#include "../common/move_type.h"
#include "./game.h"

#include <vector>
#include <string>
class ServerSerializer
{
private:
    Socket *socket;

public:
    ServerSerializer(); //Solo para testing

    explicit ServerSerializer(Socket *socket);

    void serialize_create_scenario(int32_t &scenario_code, bool *was_closed);

    void send_error_create(bool *was_closed);

    void serialize_join_scenario(const bool &join, bool *was_closed);

    void serialize_start_game(bool *was_closed);

    void send_player_id(int32_t& player_id, bool* was_closed);
    
    void send_game(GameDTO game_dto, bool *was_closed);
};
#endif
