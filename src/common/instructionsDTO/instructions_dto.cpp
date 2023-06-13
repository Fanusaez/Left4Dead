#include "instructions_dto.h"
#include <iostream>

InstructionsDTO::InstructionsDTO() {
    player_id = -1; //Utilizamos el valor -1 como valor invalido
    instruction_type = IDLE;
}

InstructionsDTO::InstructionsDTO(InstructionsType instruction) : instruction_type(instruction){
    player_id = -1;
}    

InstructionsDTO::InstructionsDTO(int& player_id, InstructionsType instruction) : 
                            player_id(player_id), instruction_type(instruction) {}

InstructionsType InstructionsDTO::get_instruction() {
    return instruction_type;
}

int InstructionsDTO::get_player_id() {
    if (player_id != -1)
        return player_id;
    else   
        return -1;
}
