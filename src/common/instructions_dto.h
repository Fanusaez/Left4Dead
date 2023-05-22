#ifndef INSTRUCTIONSDTO_H
#define INSTRUCTIONSDTO_H

#include "../common/instructions.h"
#include <vector>
//Podria ser polimorfico
class InstructionsDTO
{
private:
    Instructions instruction;

    std::vector<char> parameters;

public:
    InstructionsDTO(); //Solo para el try_pop del hilo main

    InstructionsDTO(Instructions instruction);

    InstructionsDTO(Instructions instruction, std::vector<char> parameters);

    Instructions get_instruction();

    std::vector<char> get_parameters();
};
#endif
