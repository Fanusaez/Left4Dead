#include "instructions_dto.h"
#include <iostream>

InstructionsDTO::InstructionsDTO() {}

InstructionsDTO::InstructionsDTO(InstructionsType instruction) : instruction_type(instruction){}    

InstructionsDTO::InstructionsDTO(InstructionsType instruction, std::vector<char> parameters) : 
    instruction_type(instruction), parameters(parameters){}    

InstructionsDTO::InstructionsDTO(int* player_id, InstructionsType instruction, std::vector<char> parameters) : 
    player_id(player_id), instruction_type(instruction), parameters(parameters){}

InstructionsDTO::InstructionsDTO(int* player_id, InstructionsType instruction) : parameters(),player_id(player_id), instruction_type(instruction) {}

InstructionsType InstructionsDTO::get_instruction() {
    return instruction_type;
}

int InstructionsDTO::get_player_id() {
    return *player_id;
}

std::vector<char> InstructionsDTO::get_parameters(){
    return parameters;
}