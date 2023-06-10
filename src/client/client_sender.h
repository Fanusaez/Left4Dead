#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include <atomic>
#include <vector>
#include <list>

class ClientSender : public Thread
{
private:
    Socket *socket;

    Queue<std::vector<char>> *queue_sender;

    std::atomic<bool> &keep_talking;

public:
    ClientSender(Socket *socket, std::atomic<bool> &keep_talking, 
                Queue<std::vector<char>> *queue_sender);

    void run() override;
};
#endif
