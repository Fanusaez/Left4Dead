#ifndef CLIENT_H
#define CLIENT_H

#include "../common/socket.h"
#include "../common/move.h"
#include "client_sender.h"
#include "client_receiver.h"
#include "client_serializer.h"
#include <optional>

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

public:
    Client(Socket&& socket);

    bool move(Move move);

    bool reload();

    bool shoot();

    std::optional<GameDTO> get_game();

    void join();

    void start_playing();

};
#endif
