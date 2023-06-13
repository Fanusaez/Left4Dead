#ifndef GAME_H
#define GAME_H

#include "../common/queue.h"
#include "../common/thread.h"
#include "../common/instructionsDTO/instructions_dto.h"
#include "../common/game_dto.h"
#include "game_logic.h"

#include <map>
#include <atomic>
#include <string>

class Game : public Thread {
private:
    GameLogic game_logic; //Aca esta la conexión entre el hilo y el modelo logico

    std::mutex m;   //Para proteger el map de las queue_salientes

    int32_t code;   //El codigo que tendra la partida 

    std::string game_name;  //El nombre que tiene la partida
    
    // La queue donde el player_receiver va a pushear cada instruccion
    Queue<InstructionsDTO*> queue_entrante;
 
    // Este map almacena <player_id,queue_saliente>. Voy a mandar por toda las queue el GameDTO.
    std::map<int,Queue<GameDTO> *> queue_salientes;

    bool keep_playing;  //Para controlar el gamme loop del server.

public:
    Game(Queue<GameDTO> *queue_sender, int32_t& code, std::string& game_name, int& player_id);

    void run() override;

    Queue<InstructionsDTO*> *getQueue();

    void addPlayer(Queue<GameDTO> *queue_sender, int& player_id);

    bool compare_code(const int32_t& code_to_compare);

    int32_t get_game_code();

    int get_players();

    bool compare_game_name(const std::string& game_name_to_compare);

    bool find_player(int& player_id);

    void stop_playing();

    bool is_empty();
};
#endif
