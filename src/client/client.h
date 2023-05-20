#ifndef CLIENT_H
#define CLIENT_H

#include "../common/socket.h"
#include "../common/move.h"
#include "client_sender.h"
#include "client_receiver.h"
#include "client_serializer.h"

class Client
{
private:
    Socket socket;

    std::atomic<bool> keep_talking;

    ClientSender client_sender;

    ClientReceiver client_receiver;

    ClientSerializer client_seializer;

    Queue<std::vector<char>> queue_sender;

    Queue<GameDTO> queue_receiver;

    //bool game_stage; //0 = Lobby 1 = Game

public:
    Client(char *localhost, char *puerto);

    bool create_scenario(std::string *scenario_name);

    bool join_scenario(int32_t *scenario_code);

    bool move(Move *move);

    bool start();

    GameDTO get_game();

    void join();
};
#endif
