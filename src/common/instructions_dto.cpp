#include "instructions_dto.h"

InstructionsDTO::InstructionsDTO() {}

InstructionsDTO::InstructionsDTO(Instructions instruction, std::list<char> parameters) :
    instruction(instruction), parameters(parameters) {}

InstructionsDTO::InstructionsDTO(Instructions instruction) : parameters() {}

Instructions InstructionsDTO::get_instruction()
{
    return instruction;
}

std::list<char> InstructionsDTO::get_parameters(){
    return parameters;
}