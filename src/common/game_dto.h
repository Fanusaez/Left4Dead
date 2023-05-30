#ifndef GAMEDTO_H
#define GAMEDTO_H

#include <cstdint>
#include <vector>
#include "../common/game_object_state.h"
#include "../common/soldier_type.h"

struct SoldierObjectDTO {
    int id;        // ID único del objeto
    int position_x;     
    int position_y;      
    SoldierObjectState state; // Estado del objeto
    SoldierType soldier_type;

    // Constructor para inicializar los atributos
    SoldierObjectDTO(int8_t id, int position_x, int position_y, SoldierObjectState state, SoldierType soldier_type)
        : id(id), position_x(position_x), position_y(position_y), state(state), soldier_type(soldier_type) {}
};

struct ZombieObjectDTO {
    int id;        // ID único del objeto
    int position_x;     
    int position_y;      
    ZombieObjectState state; // Estado del objeto

    // Constructor para inicializar los atributos
    ZombieObjectDTO(int8_t id, int position_x, int position_y, ZombieObjectState state)
        : id(id), position_x(position_x), position_y(position_y), state(state) {}
};

class GameDTO {
private:

    std::vector<SoldierObjectDTO> soldiers;

    std::vector<ZombieObjectDTO> zombies;

    //std::vector<SoldierObjectDTO> elements;

public:
    GameDTO();  //Lo usamos nada mas para el player_sender y client_receiver

    GameDTO(std::vector<SoldierObjectDTO> soldiers, std::vector<ZombieObjectDTO> zombies);

    void add_soldier(SoldierObjectDTO soldier);

    void add_zombie(ZombieObjectDTO zombie);
    
    std::vector<SoldierObjectDTO> get_soldiers();

    std::vector<ZombieObjectDTO> get_zombies();

};
#endif
