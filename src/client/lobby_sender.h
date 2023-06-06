#ifndef LOBBYSENDER_H
#define LOBBYSENDER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include <atomic>
#include <vector>
#include <list>

class LobbySender : public Thread
{
private:
    Socket *socket;

    Queue<std::vector<char>> *queue_sender;

    std::atomic<bool> &keep_talking;

public:
    LobbySender(Socket *socket, std::atomic<bool> &keep_talking, Queue<std::vector<char>> *queue_sender);

    void run() override;
};
#endif
