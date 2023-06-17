#ifndef GRENADEDTO_H
#define GRENADEDTO_H

#include "instructions_dto.h"
#include <stdint.h>

class GrenadeDTO : public InstructionsDTO {
private:
    uint8_t time;

public:
    explicit GrenadeDTO(int32_t& player_id, uint8_t time); 
    
    uint8_t get_time();
};
#endif
