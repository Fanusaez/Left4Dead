#ifndef INSTRUCTIONSDTO_H
#define INSTRUCTIONSDTO_H

#include "../common/instructions_type.h"
#include <vector>
//Podria ser polimorfico
class InstructionsDTO
{
private:
    InstructionsType instruction_type;
    
    std::vector<char> parameters;

    int* player_id;

public:
    InstructionsDTO(); //Solo para el try_pop del hilo main

    InstructionsDTO(InstructionsType instruction, std::vector<char> parameters);

    InstructionsDTO(InstructionsType instruction);
    
    InstructionsDTO(int* player_id, InstructionsType instruction);

    InstructionsDTO(int* player_id, InstructionsType instruction, std::vector<char> parameters);

    InstructionsType get_instruction();

    int get_player_id();

    std::vector<char> get_parameters();

    virtual ~InstructionsDTO() {}
};
#endif
