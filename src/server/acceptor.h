#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "match_mananger.h"
#include "player.h"

#include <list>

class Acceptor : public Thread{
private:
    Socket* server; //Socket que usamos para aceptar clientes. Es el socket del servidor.

    std::list <Player *> players;   //Lista de jugadores dentro de todo el servidor.

    MatchMananger match_mananger;   //Lo usaremos para manejar las distintas partidas que se crean.

public:
    explicit Acceptor(Socket* server);

    void run() override;

    void reap_dead();

    void kill_all();

    ~Acceptor() override;
};
#endif
