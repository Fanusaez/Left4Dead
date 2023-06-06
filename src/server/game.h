#ifndef GAME_H
#define GAME_H

#include "../common/queue.h"
#include "../common/thread.h"
#include "../common/instructions_dto.h"
#include "../common/game_dto.h"
#include "game_logic.h"

#include <map>
#include <atomic>

class Game : public Thread {
private:
    GameLogic game_logic;

    std::mutex m;

    int32_t code;

    std::string game_name;
    
    // La queue donde el player_receiver va a pushear es eta
    Queue<InstructionsDTO> queue_entrante;
 
    // Tengo una referencia  a la queue del sender
    std::map<int,Queue<GameDTO> *> queue_salientes;

    bool keep_playing;

public:
    Game(Queue<GameDTO> *queue_sender, int32_t *code, std::string *game_name, int *player_id);

    void run() override;

    Queue<InstructionsDTO> *getQueue();

    void addPlayer(Queue<GameDTO> *queue_sender, int *player_id);

    bool compare_code(int32_t *code_to_compare);

    int32_t get_game_code();

    int get_players();

    bool compare_game_name(std::string *game_name_to_compare);

    bool find_player(int* player_id);

    void stop_playing();

    bool is_empty();
};
#endif
