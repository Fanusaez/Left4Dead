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

    void send_create_scenario(const int32_t &scenario_code, bool *was_closed);

    void send_error_create(bool *was_closed);

    void send_join_scenario(const bool &join, bool *was_closed);

    void send_start_game(const bool &start, bool *was_closed);

    void send_player_id(const int32_t& player_id, bool* was_closed);
    
    void send_game(GameDTO game_dto, bool *was_closed);

    /*
    Metodos para testing que usaremos dentro de los metodos de arriba para no copiar codigo
    Deberian ser privados pero para los tests los ponemos publicos.
    */

    std::vector<char> serialize_create_scenario(const int32_t &scenario_code);

    std::vector<char> serialize_error_create();

    std::vector<char> serialize_join_scenario(const bool &join);

    std::vector<char> serialize_start_game(const bool &start);

    std::vector<char> serialize_player_id(const int32_t& player_id);
    
    std::vector<char> serialize_game(GameDTO game_dto);
};
#endif
