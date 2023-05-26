#include <iostream>
#include "client.h"

int main(int argc, char *argv[])
{
	Client client(argv[1], argv[2]);
	if (std::string(argv[3]) == "c"){
		std::string map = "map1";
		client.create_scenario(map);
		std::cout << "Creo el escenario" << std::endl;
	} else {
		int32_t code = 0;
		client.join_scenario(code);
		std::cout << "Joineo escenario" << std::endl;
	}
	char c;
	std::cin >> c;
	while (c != 'q') {
		GameDTO gameState = client.get_game();
		std::vector<SoldierObjectDTO> soldiers = gameState.get_soldiers();
		std::vector<ZombieObjectDTO> zombies = gameState.get_zombies();
		if (soldiers.size() == 0 || zombies.size() == 0) {
			std::cerr << "Error\n";
			client.join();
			return 1;
		}
		for (int i = 0 ; i < soldiers.size(); i++){
			SoldierObjectDTO soldier = soldiers.at(i);
			std::cout << "Id: " << soldier.id << std::endl;
			std::cout << soldier.position_x << ", " << soldier.position_y << std::endl;
			std::cout << soldier.soldier_type << ", " << soldier.state << std::endl;
		}
		for (int j = 0 ; j < zombies.size(); j++){
			ZombieObjectDTO zombie = zombies.at(j);
			std::cout << "Id: " << zombie.id << std::endl;
			std::cout << zombie.position_x << ", " << zombie.position_y << std::endl;
			std::cout << zombie.state << std::endl;
		}
		std::cin >> c;
	}
	client.join();
	return 0;
}
