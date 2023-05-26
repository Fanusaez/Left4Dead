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

    int* player_id;

public:
    InstructionsDTO(); //Solo para el try_pop del hilo main

    InstructionsDTO(int* player_id, Instructions instruction);

    InstructionsDTO(int* player_id, Instructions instruction, std::vector<char> parameters);

    Instructions get_instruction();

    int get_player_id();

    std::vector<char> get_parameters();
};
#endif
