#ifndef PLAYERRECEIVER_H
#define PLAYERRECEIVER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"
#include "server_deserializer.h"
#include "match_mananger.h"
class Cliente;

#include <atomic>
#include <vector>
#include <list>

class PlayerReceiver : public Thread{
private:

    Queue<InstructionsDTO*> *queue_receiver;

    std::atomic<bool>& stay_in_match;

    std::atomic<bool>& keep_playing;
    
    ServerDeserializer server_deserializer;

    int32_t player_id;

public:
    PlayerReceiver(Socket *socket, std::atomic<bool> &stay_in_match, 
                std::atomic<bool> &keep_playing, int32_t& player_id);

    void run() override;

    void setQueueReceiver(Queue<InstructionsDTO*> *queue_receiver);
};
#endif
