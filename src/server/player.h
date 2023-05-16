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
    Socket peer;

    //Queue de la cual vamos a sacar mensajes a senviarle a nuestro cliente
    Queue<std::vector<char>> queue_sender;

    //Referencia a la queue que tendra el hilo de partida al cual le cargamos todo.
    Queue<std::vector<char>>* queue_receiver;

    //Hilo sender
    PlayerSender player_sender;

    // Hilo receiver
    PlayerReceiver player_receiver;

    std::atomic<bool> keep_talking;

public:
    Player(Socket socket, MatchMananger *matchMananger);

    bool is_dead();

    void kill();

    void join();
};
#endif
