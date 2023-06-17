#include "game_dto.h"

GameDTO::GameDTO() : soldiers(), zombies() {}

GameDTO::GameDTO(std::vector<SoldierObjectDTO> soldiers, std::vector<ZombieObjectDTO> zombies)
 : soldiers(soldiers), zombies(zombies){}

void GameDTO::add_soldier(SoldierObjectDTO soldier){
    soldiers.push_back(soldier);
}

void GameDTO::add_zombie(ZombieObjectDTO zombie){
    zombies.push_back(zombie);
}

std::vector<SoldierObjectDTO> GameDTO::get_soldiers(){
    return soldiers;
}

std::vector<ZombieObjectDTO> GameDTO::get_zombies(){
    return zombies;
}

std::vector <GrenadeObjectDTO> GameDTO::get_elements()
{
	return this->elements;
}
