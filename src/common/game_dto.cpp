#include "game_dto.h"

GameDTO::GameDTO(){}

GameDTO::GameDTO(std::vector<GameObjectDTO> objects_game) : objects_game (objects_game){}

void GameDTO::add_object(GameObjectDTO game_object_dto){
    objects_game.push_back(game_object_dto);
}

std::vector<GameObjectDTO> GameDTO::get_objects_game(){
    return objects_game;
}