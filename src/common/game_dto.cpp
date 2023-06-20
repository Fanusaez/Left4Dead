#include "game_dto.h"
#include <iostream>

GameDTO::GameDTO() : soldiers(), zombies(), elements(){}

GameDTO::GameDTO(std::vector<SoldierObjectDTO> soldiers, std::vector<ZombieObjectDTO> zombies)
 : soldiers(soldiers), zombies(zombies), elements(elements){}

void GameDTO::add_soldier(SoldierObjectDTO soldier){
    soldiers.push_back(soldier);
}

void GameDTO::add_zombie(ZombieObjectDTO zombie){
    zombies.push_back(zombie);
}

void GameDTO::add_element(GrenadeObjectDTO element){
    elements.push_back(element);
}

std::vector<SoldierObjectDTO> GameDTO::get_soldiers(){
    return soldiers;
}

std::vector<ZombieObjectDTO> GameDTO::get_zombies(){
    return zombies;
}

std::vector <GrenadeObjectDTO> GameDTO::get_elements()
{
	return elements;
}
