#ifndef JOINDTO_H
#define JOINDTO_H

#include "instructions_dto.h"
#include <stdint.h>

class JoinDTO : public InstructionsDTO {
private:
    int32_t game_code;

    bool could_join;

public:
    JoinDTO(int* player_id, int32_t game_code); 

    explicit JoinDTO(bool could_join); 
    
    int32_t get_game_code();

    bool get_could_join();
};
#endif
