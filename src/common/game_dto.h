#ifndef GAMEDTO_H
#define GAMEDTO_H

#include <cstdint>
#include <vector>
#include "../common/game_object_state.h"

struct GameObjectDTO {
    int id;        // ID único del objeto
    uint16_t position_x;     
    uint16_t position_y;      
    GameObjectState state; // Estado del objeto

    // Constructor para inicializar los atributos
    GameObjectDTO(const int id, uint16_t position_x, uint16_t position_y, GameObjectState state)
        : id(id), position_x(position_x), position_y(position_y), state(state) {}
};

class GameDTO {
private:

    std::vector<GameObjectDTO> objects_game;

public:
    GameDTO();  //Lo usamos nada mas para el player_sender y client_receiver

    GameDTO(std::vector<GameObjectDTO> objects_game);

    void add_object(GameObjectDTO game_object_dto);

    std::vector<GameObjectDTO> get_objects_game();
};
#endif
