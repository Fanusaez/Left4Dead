#include "acceptor.h"
#include <iostream>
#include <utility>

Acceptor::Acceptor(Socket *server) : server(server) {}

void Acceptor::run() {
    while (true) {
        Socket socket_player;
        try {
            socket_player = server->accept();
        }
        catch (const std::invalid_argument& e) {
            break;
        }
        //Le muevo el socket al cliente para que se maneje el en enviar y recibir mensajes
        //Player *nuevo = new Player(std::move(socket_player), &player_mananger);

        //players_mananger -> add_player(nuevo);

        //reap_dead();
    }
    //kill_all();
}

Acceptor::~Acceptor() {}
