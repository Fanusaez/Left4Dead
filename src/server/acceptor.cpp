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
        std::cout<<"Nuevo jugador"<<std::endl;
        //Le muevo el socket al cliente para que se maneje el en enviar y recibir mensajes
        //Le pasamos la cantidad de jugadores que hay y ese sera su id.
        Player *new_player = new Player(std::move(socket_player), 
                            &match_mananger, int(players.size()));

        //Agergo mi jugador a mi lista de jugadores
        players.push_back(new_player);

        //Me fijo si algun jugador se desconecto
        reap_dead();
    }
    //Si se cierra el servidor cierro todas las partidas creadas
    match_mananger.joinGames();
    //Cierro y elimino tambien a los clientes creados
    kill_all();
}

void Acceptor::reap_dead()
{
    players.remove_if([](Player *c)
                      {
    if (c->is_dead()) {
        c->join();  //Si se murio le hago un join al cliente
        delete c;   //Elimino el objeto player
        return true;
    }
    return false; });
}

void Acceptor::kill_all()
{
    for (Player *c : players)
    {
        c->kill();
        c->join();
        delete c;
    }
    players.clear();
}

Acceptor::~Acceptor() {}
