#ifndef PLAYERESENDER_H
#define PLAYERESENDER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include <atomic>
#include <vector>

class PlayerSender : public Thread{
private:
    Socket* socket;
    
    std::atomic<bool>& keep_talking;

    Queue<std::vector<char>>* q;

public:
    PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, 
                Queue<std::vector<char>> *q);

    void run() override;    
};
#endif
