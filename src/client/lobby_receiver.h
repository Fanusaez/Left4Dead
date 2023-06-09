#ifndef LOBBYRECEIVER_H
#define LOBBYRECEIVER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include "../common/instructionsDTO/instructions_dto.h"
#include "lobby_deserializer.h"

#include <atomic>
#include <vector>
#include <list>

class LobbyReceiver : public Thread
{
private:
    Queue<InstructionsDTO*> *queue_receiver;

    std::atomic<bool> &keep_talking;
    
    LobbyDeserializer lobby_deserializer;

public:
    LobbyReceiver(Socket *socket, std::atomic<bool> &keep_talking, Queue<InstructionsDTO*> *queue_receiver);

    void run() override;

};
#endif
