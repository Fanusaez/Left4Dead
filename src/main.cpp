#include "client.h"
#include "lobby.h"
#include "client/game.h"

#include <iostream>
#include <exception>
#include <unistd.h>
#include <string>
#include <list>
#include <memory>
#include <sstream>

#include "./graphics_lobby/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	/*
	Gameloop donde estoy en el lobby. Todo el tiempo estoy chequeando nuevos mensajes de server 
	ya sea por el create o el join o la lista de partidas o el chat
	*/
 	Lobby lobby(argv[1], argv[2]);
	int32_t player_id = lobby.get_player_id();
 	try {
		QApplication app(argc, argv);
		MainWindow w(&lobby);
		w.show();
		if (app.exec()) {
				std::cout<<"EXIT"<<std::endl;
				throw std::runtime_error("La aplicación QT finalizó de forma incorrecta");
		} 
	} catch (const std::runtime_error& e) {
		lobby.close();
		return 0;
	}
 	/*while (lobby.running()) {
		std::string input;
		std::getline(std::cin, input);

		std::istringstream iss(input);
		std::string mode;
		iss >> mode;

		if (mode == "create") {
			std::string map;
			iss >> map;
			lobby.create_scenario(map,SURVIVAL,1);
			lobby.start();
			lobby.soldier_type(SCOUT);
		} else if (mode == "join") {
			if (iss.eof()) {
				std::cout<<"Error: se requiere un código para unirse a un escenario."<<std::endl;
				continue;  // Vuelve al inicio del bucle
        	}
			int32_t code;
			iss >> code;
			lobby.join_scenario(code);
			lobby.start();
			lobby.soldier_type(IDF);
		} else if (mode == "start") {
			//lobby.start();
			break;
		} else if (mode == "quit") {
			lobby.close();
			return 0;
		}
		lobby.update();
	} */

	Socket socket = lobby.move_socket();
	MainGame mainGame(player_id, socket);
	mainGame.start();

	return 0;
}
