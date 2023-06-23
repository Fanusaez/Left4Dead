#ifndef CREATEDTO_H
#define CREATEDTO_H

#include "instructions_dto.h"
#include "../game_mode.h"
#include <string>

class CreateDTO : public InstructionsDTO {
private:
    std::string scenario_name;

    int32_t game_code;

    GameMode game_mode;

    int8_t game_players;

public:
    CreateDTO(int32_t& player_id, std::string scenario_name, GameMode game_mode, int8_t game_players); 

    explicit CreateDTO(int32_t game_code); 

    std::string get_scenario_name();

    int32_t get_game_code();

    GameMode get_game_mode();

    int8_t get_game_players();

    virtual ~CreateDTO() {}
};
#endif
