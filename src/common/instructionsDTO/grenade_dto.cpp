#include "grenade_dto.h"

GrenadeDTO::GrenadeDTO(int32_t& player_id, uint8_t time) : InstructionsDTO(player_id,GRENADE),
                                                            time(time){}

uint8_t GrenadeDTO::get_time() {
    return time;
}