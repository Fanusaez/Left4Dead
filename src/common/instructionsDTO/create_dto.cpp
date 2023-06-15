#include "create_dto.h"
#include <iostream>

CreateDTO::CreateDTO(int32_t& player_id, std::string scenario_name) : 
    InstructionsDTO(player_id,CREATE), scenario_name(scenario_name) {}

CreateDTO::CreateDTO(int32_t game_code) : InstructionsDTO(CREATE), game_code(game_code) {}

std::string CreateDTO::get_scenario_name(){ 
    return scenario_name;
}

int32_t CreateDTO::get_game_code(){ return game_code;}
