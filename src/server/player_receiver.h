#ifndef PLAYERRECEIVER_H
#define PLAYERRECEIVER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "match_mananger.h"
#include "../common/queue.h"
class Cliente;

#include <atomic>
#include <vector>
#include <list>

class PlayerReceiver : public Thread{
private:
    MatchMananger *match_manager;

    Queue<std::vector<char>> *queue_receiver;

    std::atomic<bool>& keep_talking;

public:
    PlayerReceiver(Socket *socket, MatchMananger *match_manager, std::atomic<bool> &keep_talking);

    void run() override;

    void setQueueReceiver(Queue<std::vector<char>> *queue_receiver);
};
#endif
