#ifndef MOVEDTO_H
#define MOVEDTO_H

#include "instructions_dto.h"
#include "../move_type.h"

class MoveDTO : public InstructionsDTO {
private:
    MoveType move_type;

public:
    MoveDTO(int* player_id, MoveType move_type); 

    MoveType get_move_type();
};
#endif
