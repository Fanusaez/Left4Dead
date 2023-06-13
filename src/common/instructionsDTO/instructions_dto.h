#ifndef INSTRUCTIONSDTO_H
#define INSTRUCTIONSDTO_H

#include "../common/instructions_type.h"
#include <vector>
//Podria ser polimorfico
class InstructionsDTO
{
private:
    InstructionsType instruction_type;
    
    int player_id;

public:
    InstructionsDTO(); //Solo para el try_pop del hilo main

    explicit InstructionsDTO(InstructionsType instruction);
    
    InstructionsDTO(int& player_id, InstructionsType instruction);

    InstructionsType get_instruction();

    int get_player_id();

    virtual ~InstructionsDTO() {}
};
#endif
