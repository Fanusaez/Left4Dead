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
        Player *new_player = new Player(std::move(socket_player), &match_mananger, int(players.size()));

        //Agergo mi jugador a mi lista de jugadores
        players.push_back(new_player);

        reap_dead();
    }
    match_mananger.joinGames();
    kill_all();
}

void Acceptor::reap_dead()
{
    players.remove_if([](Player *c)
                      {
    if (c->is_dead()) {
        c->join();
        delete c;
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
