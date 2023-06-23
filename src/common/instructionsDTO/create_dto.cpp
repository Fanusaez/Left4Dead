#include "create_dto.h"
#include <iostream>

CreateDTO::CreateDTO(int32_t& player_id, std::string scenario_name, GameMode game_mode, int8_t game_players) : 
    InstructionsDTO(player_id,CREATE), scenario_name(scenario_name), game_mode(game_mode), game_players(game_players) {}

CreateDTO::CreateDTO(int32_t game_code) : InstructionsDTO(CREATE), game_code(game_code) {}

std::string CreateDTO::get_scenario_name(){ 
    return scenario_name;
}

int32_t CreateDTO::get_game_code(){ return game_code;}

GameMode CreateDTO::get_game_mode() {return game_mode;}

int8_t CreateDTO::get_game_players() {return game_players;}
