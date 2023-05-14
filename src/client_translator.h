#ifndef CLIENTTRANSLATOR_H
#define CLIENTTRANSLATOR_H

#include <vector>
#include <string>

#include "../src/game_mode.h"
#include "../src/soldier_type.h"
#include "../src/move.h"

class ClientTranslator{
private:

public:
    /*----------------------Lobby message--------------------*/

    std::vector<char> translate_create_scenario(std::string *scenario_name);

    std::vector<char> translate_join_scenario(int32_t *scenario_code);

    std::vector<char> translate_game_mode(GameMode *game_mode);

    std::vector<char> translate_soldier(SoldierType *soldier_type);

    /*----------------------Game message--------------------*/

    std::vector<char> translate_move(Move *move);

    std::vector<char> translate_reloading();
};
#endif
