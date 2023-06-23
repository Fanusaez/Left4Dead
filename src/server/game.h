#ifndef GAME_H
#define GAME_H

#include "../common/queue.h"
#include "../common/thread.h"
#include "../common/instructionsDTO/instructions_dto.h"
#include "../common/game_dto.h"
#include "../common/game_mode.h"
#include "./protected_outputs_queue.h"
#include "game_logic.h"

#include <map>
#include <atomic>
#include <string>

class Game : public Thread {
private:
    GameLogic game_logic; //Aca esta la conexión entre el hilo y el modelo logico

    ProtectedOutputsQueue protected_outputs_queue;
    
    //std::mutex m;   //Para proteger el map de las queue_salientes

    int32_t code;   //El codigo que tendra la partida 

    std::string game_name;  //El nombre que tiene la partida
    
    // La queue donde el player_receiver va a pushear cada instruccion
    Queue<InstructionsDTO*> queue_entrante;
 
    // Este map almacena <player_id,queue_saliente>. Voy a mandar por toda las queue el GameDTO.
    //std::map<int,Queue<GameDTO> *> queue_salientes;

    bool keep_playing;  //Para controlar el gamme loop del server.

    bool admit_players; //Para controlar si se pueden unir jugadores o no

    int8_t game_players;

public:
    Game(Queue<GameDTO> *queue_sender, int32_t& code, std::string& game_name, int32_t& player_id,
        GameMode& game_mode, int8_t& game_players);

    void run() override;

    Queue<InstructionsDTO*> *getQueue();

    void addPlayer(Queue<GameDTO> *queue_sender, int32_t& player_id);

    bool compare_code(const int32_t& code_to_compare);

    int32_t get_game_code();

    bool compare_game_name(const std::string& game_name_to_compare);

    bool delete_player(int32_t& player_id);

    void stop_playing();

    bool is_empty();

    bool can_join();

    bool is_not_playing();
};
#endif
