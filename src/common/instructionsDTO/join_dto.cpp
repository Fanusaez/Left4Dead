#include "join_dto.h"

JoinDTO::JoinDTO(int32_t& player_id, int32_t game_code) : 
InstructionsDTO(player_id,JOIN), game_code(game_code){} 

JoinDTO::JoinDTO(bool could_join) : InstructionsDTO(JOIN), could_join(could_join){} 

int32_t JoinDTO::get_game_code() {return game_code;}

bool JoinDTO::get_could_join() {return could_join;}
