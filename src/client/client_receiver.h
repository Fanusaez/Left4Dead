#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include "../common/game_dto.h"

#include <atomic>
#include <vector>
#include <list>

class ClientReceiver : public Thread
{
private:
    Socket *socket;

    Queue<GameDTO> *queue_receiver;

    std::atomic<bool> &keep_talking;

public:
    ClientReceiver(Socket *socket, std::atomic<bool> &keep_talking, Queue<GameDTO> *queue_receiver);

    void run() override;

};
#endif
