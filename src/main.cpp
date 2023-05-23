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
		std::vector<GameObjectDTO> gameObjects = gameState.get_objects_game();
		if (gameObjects.size() != 1) {
			std::cerr << "Error\n";
			client.join();
			return 1;
		}
		GameObjectDTO playerDTO = gameObjects.front();
		std::cout << "Id: " << playerDTO.id << std::endl;
		std::cout << playerDTO.position_x << ", " << playerDTO.position_y << std::endl;
		std::cin >> c;
	}
	client.join();
	return 0;
}
