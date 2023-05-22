#include "instructions_dto.h"
#include <iostream>

InstructionsDTO::InstructionsDTO() {}

InstructionsDTO::InstructionsDTO(Instructions instruction, std::vector<char> parameters) :
    instruction(instruction), parameters(parameters) {
    }

InstructionsDTO::InstructionsDTO(Instructions instruction) : parameters() {}

Instructions InstructionsDTO::get_instruction()
{
    return instruction;
}

std::vector<char> InstructionsDTO::get_parameters(){
    return parameters;
}