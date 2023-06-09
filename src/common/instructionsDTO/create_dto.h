#ifndef CREATEDTO_H
#define CREATEDTO_H

#include "instructions_dto.h"
#include <string>

class CreateDTO : public InstructionsDTO {
private:
    std::string scenario_name;

    int32_t game_code;

public:
    CreateDTO(int* player_id, std::string scenario_name); 

    CreateDTO(int32_t game_code); 

    std::string get_scenario_name();

    int32_t get_game_code();
};
#endif
