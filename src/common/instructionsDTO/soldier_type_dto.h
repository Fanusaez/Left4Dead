#ifndef SOLDIERTYPEDTO_H
#define SOLDIERTYPEDTO_H

#include "instructions_dto.h"
#include "../soldier_type.h"

class SoldierTypeDTO : public InstructionsDTO {
private:
    SoldierType soldier_type;

    int32_t game_code;

public:
    SoldierTypeDTO(int32_t& player_id, SoldierType soldier_type); 

    explicit SoldierTypeDTO(SoldierType soldier_type); 

    SoldierType get_soldier_type();

    virtual ~SoldierTypeDTO() {}
};
#endif
