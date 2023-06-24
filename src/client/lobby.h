#ifndef LOBBY_H
#define LOBBY_H

#include "../common/socket.h"
#include "lobby_sender.h"
#include "lobby_receiver.h"
#include "lobby_serializer.h"
#include "lobby_deserializer.h"
#include <optional>
#include <vector>
#include <string>

class Lobby
{
private:
    int32_t player_id;

    Socket socket;

    std::atomic<bool> keep_talking;

    LobbySender lobby_sender;

    LobbyReceiver lobby_receiver;

    LobbySerializer lobby_serializer; 
    
    Queue<std::vector<char>> queue_sender;

    Queue<InstructionsDTO*> queue_receiver;

    void get_create(InstructionsDTO* instruction_dto);

    void get_join(InstructionsDTO* instruction_dto);

    void get_start(InstructionsDTO* instruction_dto);


public:
    void exit_lobby();
    
    Lobby(char *localhost, char *puerto);

    bool running();

    bool create_scenario(const std::string& scenario_name);

    bool create_scenario(const std::string& scenario_name, const GameMode& game_mode, const int8_t& game_players);

    bool join_scenario(const int32_t& scenario_code);

    void soldier_type(const SoldierType& soldier_type);

    void start();

    void set_game_list();

    void close();

    Socket move_socket();

    void update();

    int get_player_id();
};
#endif
