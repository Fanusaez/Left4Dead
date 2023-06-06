#include "instructions_dto.h"
#include <iostream>

InstructionsDTO::InstructionsDTO() {}

InstructionsDTO::InstructionsDTO(Instructions instruction, std::vector<char> parameters) : 
    instruction(instruction), parameters(parameters){}    

InstructionsDTO::InstructionsDTO(int* player_id, Instructions instruction, std::vector<char> parameters) : 
    player_id(player_id), instruction(instruction), parameters(parameters){}

InstructionsDTO::InstructionsDTO(int* player_id, Instructions instruction) : parameters(),player_id(player_id), instruction(instruction) {}

Instructions InstructionsDTO::get_instruction() {
    return instruction;
}

int InstructionsDTO::get_player_id() {
    return *player_id;
}

std::vector<char> InstructionsDTO::get_parameters(){
    return parameters;
}