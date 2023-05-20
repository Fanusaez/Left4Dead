#ifndef INSTRUCTIONSDTO_H
#define INSTRUCTIONSDTO_H

#include "../common/instructions.h"
#include <list>
//Podria ser polimorfico
class InstructionsDTO
{
private:
    Instructions instruction;

    std::list<char> parameters;

public:
    InstructionsDTO(); //Solo para el try_pop del hilo main

    InstructionsDTO(Instructions instruction);

    InstructionsDTO(Instructions instruction, std::list<char> parameters);

    Instructions get_instruction();

    std::list<char> get_parameters();
};
#endif
