#include "move_dto.h"

MoveDTO::MoveDTO(int* player_id, MoveType move_type) : 
        InstructionsDTO(player_id,MOVE), move_type(move_type) {}

MoveType MoveDTO::get_move_type(){ return move_type;}
