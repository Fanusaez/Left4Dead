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
    int player_id;

    Socket peer;

    //Hilo sender
    PlayerSender player_sender;

    std::atomic<bool> keep_talking;

public:
    Player(Socket socket, MatchMananger *matchMananger, int player_id);

    bool is_dead();

    void kill();

    void join();
};
#endif
