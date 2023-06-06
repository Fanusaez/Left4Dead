#ifndef LOBBY_H
#define LOBBY_H

#include "../common/socket.h"
#include "lobby_sender.h"
#include "lobby_receiver.h"
#include "lobby_serializer.h"
#include "lobby_deserializer.h"
#include <optional>

class Lobby
{
private:
    Socket socket;

    std::atomic<bool> keep_talking;

    LobbySender lobby_sender;

    LobbyReceiver lobby_receiver;

    LobbySerializer lobby_seializer; 
    
    Queue<std::vector<char>> queue_sender;

    Queue<InstructionsDTO> queue_receiver;

public:
    Lobby(char *localhost, char *puerto);

    bool running();

    bool create_scenario(const std::string& scenario_name);

    bool join_scenario(const int32_t& scenario_code);

    void start();

    void set_game_code(const int32_t &game_code);

    void set_game_list();

    void close();

    Socket move_socket();

    void update();

};
#endif
