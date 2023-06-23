#ifndef GAMEDTO_H
#define GAMEDTO_H

#include <cstdint>
#include <vector>
#include "../common/game_object_state.h"
#include "../common/soldier_type.h"
#include "../common/zombie_type.h"
#include "../common/grenade_type.h"

struct SoldierObjectDTO {
    int32_t player_id;      //ID del playe. Este es unico en el servidor
    int16_t id;        // ID único del objeto en el juego
    int16_t health;
    int16_t position_x;     
    int16_t position_y;      
    int16_t bullets;
    int16_t time_explosive_grenade;
    int16_t time_smoke_grenade;
    int16_t time_air_strike;
    SoldierObjectState state;   //Estado del objeto
    SoldierType soldier_type;   //Tipo de soldado
    bool facing_left;

    // Constructor para inicializar los atributos
    SoldierObjectDTO(int32_t player_id, int16_t id, int16_t health, int16_t position_x, 
                    int16_t position_y, uint16_t bullets, int16_t time_explosive_grenade,
                    int16_t time_smoke_grenade, int16_t time_air_strike, SoldierObjectState state, 
                    SoldierType soldier_type, bool facing_left) : player_id(player_id), id(id),
                    health(health), position_x(position_x), position_y(position_y), 
                    bullets(bullets), time_explosive_grenade(time_explosive_grenade),
                    time_smoke_grenade(time_smoke_grenade), time_air_strike(time_air_strike),
                    state(state), soldier_type(soldier_type), facing_left(facing_left) {}
};

struct ZombieObjectDTO {
    int16_t id;        // ID único del objeto
    int16_t health;
    int16_t position_x;     
    int16_t position_y;      
    ZombieObjectState state; // Estado del objeto
    ZombieType zombie_type;
    bool facing_left;

    // Constructor para inicializar los atributos
    ZombieObjectDTO(int16_t id, int16_t health, int16_t position_x, int16_t position_y, 
                    ZombieObjectState state, ZombieType zombie_type, bool facing_left) : 
                    id(id), health(health), position_x(position_x), position_y(position_y),
                    state(state), zombie_type(zombie_type), facing_left(facing_left) {}
};

struct GrenadeObjectDTO {
    int16_t id;        // ID único del objeto
    int16_t position_x;     
    int16_t position_y;      
    GrenadeType grenade_type;

    // Constructor para inicializar los atributos
    GrenadeObjectDTO(int16_t id, int16_t position_x, int16_t position_y,
                        GrenadeType grenade_type) 
                    : id(id), position_x(position_x), position_y(position_y), 
                    grenade_type(grenade_type){}
};

struct GameStats {
    int16_t total_bullets;
    int16_t total_dead_zombies;

    GameStats(int16_t total_bullets, int16_t total_dead_zombies) :
                total_bullets(total_bullets), total_dead_zombies(total_dead_zombies){}
};

class GameDTO {
private:
    std::vector<SoldierObjectDTO> soldiers;

    std::vector<ZombieObjectDTO> zombies;

    std::vector<GrenadeObjectDTO> elements;

    bool end_game;  //Lo uso para avisarle cuando termina el juego

    GameStats game_stats;

public:
    GameDTO();  //Lo usamos nada mas para el player_sender y client_receiver

    GameDTO(std::vector<SoldierObjectDTO> soldiers, std::vector<ZombieObjectDTO> zombies);

    void add_soldier(SoldierObjectDTO soldier);

    void add_zombie(ZombieObjectDTO zombie);

    void add_element(GrenadeObjectDTO element);

    void add_game_stats(GameStats game_stats);
    
    void set_end_game(bool end_game);
    
    std::vector<SoldierObjectDTO> get_soldiers();

    std::vector<ZombieObjectDTO> get_zombies();

    std::vector<GrenadeObjectDTO> get_elements();

    GameStats get_game_stats();

    bool is_end_game();
};
#endif
