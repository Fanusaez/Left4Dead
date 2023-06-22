#include "soldier_type_dto.h"

SoldierTypeDTO::SoldierTypeDTO(int32_t& player_id, SoldierType soldier_type) : 
    InstructionsDTO(player_id,SOLDIER_TYPE), soldier_type(soldier_type) {}

SoldierType SoldierTypeDTO::get_soldier_type(){ 
    return soldier_type;
}
