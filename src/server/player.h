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
    int32_t player_id;  //Es el player_id unico dentro el servidor.

    Socket peer;    //Es el socket que tendra cada jugador dentro del servidor.

    //Hilo sender
    PlayerSender player_sender; //Hilo que se encargara de enviar mensajes al cliente.

    std::atomic<bool> stay_in_match; //Con este booleano nos vamos del juego pero podemos seguir
                                    //en el server para conectarnos a otra partida.

    std::atomic<bool> keep_playing; //Para cortar el loop en el hilo sender y el hilo receiver.
                                    //Se pone en false cuando queremos desconectar al jugador.

public:
    Player(Socket socket, MatchMananger *matchMananger, int32_t player_id);

    bool is_dead();

    void kill();

    void join();
};
#endif
