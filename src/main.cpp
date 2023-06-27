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

	Socket socket = lobby.move_socket();
	MainGame mainGame(player_id, socket);
	mainGame.start();

	return 0;
}
