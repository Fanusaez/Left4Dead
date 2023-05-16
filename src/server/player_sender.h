#ifndef PLAYERESENDER_H
#define PLAYERESENDER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include "player_receiver.h"

#include <atomic>
#include <vector>

class PlayerSender : public Thread{
private:
    Socket* socket;
    
    std::atomic<bool>& keep_talking;

    // Queue de la cual vamos a sacar mensajes a senviarle a nuestro cliente
    Queue<std::vector<char>> queue_sender;

    // Hilo receiver
    PlayerReceiver player_receiver;

    // Referencia a la queue que tendra el hilo de Game al cual le cargamos todo.
    Queue<std::vector<char>> *queue_receiver;

    //Esta referencia es unicamente para el proceso inicial de create/join
    MatchMananger *match_mananger;

public:
    PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, MatchMananger *matchMananger);

    void run() override;

    void joinPlayerReceiver();

    void initPlayerReceiver();
};
#endif
