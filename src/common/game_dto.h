#ifndef GAMEDTO_H
#define GAMEDTO_H

#include <cstdint>
#include <vector>
#include "../common/game_object_state.h"
#include "../common/soldier_type.h"
#include "../common/zombie_type.h"

struct SoldierObjectDTO {
    int player_id;      //ID del playe. Este es unico en el servidor
    int16_t id;        // ID único del objeto en el juego
    int16_t health;
    int16_t position_x;     
    int16_t position_y;      
    int16_t bullets;
    SoldierObjectState state;   //Estado del objeto
    SoldierType soldier_type;   //Tipo de soldado
    bool facing_left;

    // Constructor para inicializar los atributos
    SoldierObjectDTO(int player_id, int16_t id, int16_t health, int16_t position_x, 
                    int16_t position_y, uint16_t bullets, SoldierObjectState state, 
                    SoldierType soldier_type, bool facing_left) : player_id(player_id), id(id),
                    health(health), position_x(position_x), position_y(position_y), state(state),
                    soldier_type(soldier_type), facing_left(facing_left) {}
};

struct ZombieObjectDTO {
    int16_t id;        // ID único del objeto
    int16_t position_x;     
    int16_t position_y;      
    ZombieObjectState state; // Estado del objeto
    ZombieType zombie_type;
    bool facing_left;

    // Constructor para inicializar los atributos
    ZombieObjectDTO(int16_t id, int16_t position_x, int16_t position_y, ZombieObjectState state, 
                    ZombieType zombie_type, bool facing_left) : id(id), position_x(position_x),
                    position_y(position_y), state(state), zombie_type(zombie_type), 
                    facing_left(facing_left) {}
};

class GameDTO {
private:
    std::vector<SoldierObjectDTO> soldiers;

    std::vector<ZombieObjectDTO> zombies;

    //std::vector<ElementsObjectDTO> elements;

public:
    GameDTO();  //Lo usamos nada mas para el player_sender y client_receiver

    GameDTO(std::vector<SoldierObjectDTO> soldiers, std::vector<ZombieObjectDTO> zombies);

    void add_soldier(SoldierObjectDTO soldier);

    void add_zombie(ZombieObjectDTO zombie);
    
    std::vector<SoldierObjectDTO> get_soldiers();

    std::vector<ZombieObjectDTO> get_zombies();
};
#endif
