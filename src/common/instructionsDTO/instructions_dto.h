#ifndef INSTRUCTIONSDTO_H
#define INSTRUCTIONSDTO_H

#include "../instructions_type.h"
#include <vector>
#include <cstdint>

class InstructionsDTO
{
private:
    InstructionsType instruction_type;
    
    int32_t player_id;

public:
    InstructionsDTO(); //Solo para el try_pop del hilo main

    explicit InstructionsDTO(InstructionsType instruction);
    
    InstructionsDTO(int32_t& player_id, InstructionsType instruction);

    InstructionsType get_instruction();

    int get_player_id();

    virtual ~InstructionsDTO() {}
};
#endif
