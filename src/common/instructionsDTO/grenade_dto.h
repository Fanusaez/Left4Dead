#ifndef GRENADEDTO_H
#define GRENADEDTO_H

#include "instructions_dto.h"
#include "../grenade_type.h"
#include <stdint.h>

class GrenadeDTO : public InstructionsDTO {
private:
    uint8_t time;

    GrenadeType grenade_type;

public:
    explicit GrenadeDTO(int32_t& player_id, uint8_t time, GrenadeType grenade_type); 
    
    uint8_t get_time();

    GrenadeType get_grenade_type();
};
#endif
