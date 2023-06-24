#ifndef GRENADEDTO_H
#define GRENADEDTO_H

#include "instructions_dto.h"
#include "../grenade_type.h"
#include <stdint.h>

class GrenadeDTO : public InstructionsDTO {
private:
    int32_t time;

    GrenadeType grenade_type;

public:
    explicit GrenadeDTO(int32_t& player_id, int32_t time, GrenadeType grenade_type); 
    
    int32_t get_time();

    GrenadeType get_grenade_type();
};
#endif
