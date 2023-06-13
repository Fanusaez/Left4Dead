#ifndef PALYER_H
#define PALYER_H

#include "../common/thread.h"
#include "../common/queue.h"
#include "player_sender.h"
#include "player_receiver.h"
#include "../common/socket.h"

#include <atomic>
#include <list>
#include <vector>

class Player{
private:
    int player_id;  //Es el player_id unico dentro el servidor.

    Socket peer;    //Es el socket que tendra cada jugador dentro del servidor.

    //Hilo sender
    PlayerSender player_sender; //Hilo que se encargara de enviar mensajes al cliente.

    std::atomic<bool> keep_talking; //Para cortar el loop en el hilo sender y el hilo receiver.

public:
    Player(Socket socket, MatchMananger *matchMananger, int player_id);

    bool is_dead();

    void kill();

    void join();
};
#endif
