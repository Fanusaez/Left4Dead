#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include "../common/game_dto.h"
#include "client_deserializer.h"

#include <atomic>
#include <vector>
#include <list>

class ClientReceiver : public Thread
{
private:
    Queue<GameDTO> *queue_receiver;

    std::atomic<bool> &keep_talking;

    ClientDeserializer client_deserializer;

public:
    ClientReceiver(Socket *socket, std::atomic<bool> &keep_talking, Queue<GameDTO> *queue_receiver);

    void run() override;
};
#endif
