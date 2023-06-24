#include "grenade_dto.h"

GrenadeDTO::GrenadeDTO(int32_t& player_id, int32_t time, GrenadeType grenade_type) : 
    InstructionsDTO(player_id, (grenade_type == SMOKE_GRENADE) ? THROW_SMOKE_GRENADE : THROW_EXPLOSIVE_GRENADE),
    time(time),
    grenade_type(grenade_type) {
}

int32_t GrenadeDTO::get_time() {
    return time;
}

GrenadeType GrenadeDTO::get_grenade_type() {
    return grenade_type;
}