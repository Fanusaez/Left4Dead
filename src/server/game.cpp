#include "game.h"
#include "../common/move_type.h"
#include "../common/instructionsDTO/soldier_type_dto.h"
#include <unistd.h>
#include <chrono>
#include <string>

double rate = 0.05;

Game::Game(Queue<GameDTO> *queue_sender, int32_t& code, std::string& game_name, int32_t& player_id,
    GameMode& game_mode, int8_t& game_players) : queue_entrante(10000), code(code),
    game_name(game_name), game_logic(game_mode), keep_playing(true), admit_players(true),
    game_players(game_players) {
    //game_logic.add_soldier_scout(player_id);
    //queue_salientes[player_id] = queue_sender;
    protected_outputs_queue.add_queue(queue_sender,player_id);
}

void Game::run(){   
    InstructionsDTO* instructionDTO;
    bool could_pop;
    int start_players = 0;
    //Espero a popoear la señal de start de todos los jugadores
    while (start_players <  protected_outputs_queue.number_of_players() && keep_playing) {
        try {
            could_pop = queue_entrante.try_pop(instructionDTO);  
            if(could_pop) {
                if (instructionDTO->get_instruction() == START) {
                    start_players++;
                    delete instructionDTO;
                }
                else if (instructionDTO->get_instruction() == SOLDIER_TYPE) {
                    SoldierTypeDTO* soldier_dto = dynamic_cast<SoldierTypeDTO*>(instructionDTO);
                    if (soldier_dto->get_soldier_type() == IDF)
                        game_logic.add_soldier_idf(soldier_dto->get_player_id());
                    else if (soldier_dto->get_soldier_type() == SCOUT)
                        game_logic.add_soldier_scout(soldier_dto->get_player_id());
                    else if (soldier_dto->get_soldier_type() == P90)
                        game_logic.add_soldier_p90(soldier_dto->get_player_id());
                    delete instructionDTO;
                }
            }
		std::this_thread::sleep_for(std::chrono::duration<double>(rate));
        } catch (const ClosedQueue& e) {
            std::cout<<"Juego finalizado"<<std::endl;
            keep_playing = false;
            return;
        }
    }
    //Comienza el juego
    admit_players = false;
    while (keep_playing)
    {
        auto t_start = std::chrono::high_resolution_clock::now();   //Comienzo el timer
        could_pop = queue_entrante.try_pop(instructionDTO); //
        int instructions_count = 0;
        while (could_pop && instructions_count < 10) { //Controlar: cantidad y si no hay mas
            game_logic.new_instruction(instructionDTO); //La logica analiza la instruccion
            delete instructionDTO;  //Elimino la instruccion ya que no la necesito mas
            could_pop = queue_entrante.try_pop(instructionDTO); //Busco la proxima
            instructions_count++;
        }
        game_logic.udpate_game(); //Una vez que analize las instrucciones actualizo el juego.
        GameDTO game_dto = game_logic.get_game(); //Obtengo el "screen" del juego
        keep_playing = !game_logic.game_over();
        //Comienzo a mandarlo a todas las queue de los clientes del juego
        protected_outputs_queue.push_game(game_dto);
        //Me fijo cuanto tardo y calculo cuanto dormir o si seguir corriendo para mantener el rate.
        auto t_end = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> duration = t_end - t_start;
		double seconds = duration.count();
		double rest = rate - seconds;
		if(rest < 0) {
			double behind = -rest;
        	double lost = behind - std::fmod(behind, rate);
        	t_start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>
                                                        (std::chrono::duration<double>(lost));
		} else {
			std::this_thread::sleep_for(std::chrono::duration<double>(rest));
		}
    }
    GameDTO game_dto = game_logic.get_game();
    game_dto.set_end_game(true);
    protected_outputs_queue.push_game(game_dto);
    queue_entrante.close();
}

Queue<InstructionsDTO*> *Game::getQueue(){
    return &queue_entrante;
}

void Game::addPlayer(Queue<GameDTO> *queue_sender,int32_t& player_id){
    game_logic.add_soldier_scout(player_id);
    protected_outputs_queue.add_queue(queue_sender,player_id);
}

bool Game::compare_code(const int32_t& code_to_compare){
    return (code == code_to_compare);
}

bool Game::compare_game_name(const std::string& game_name_to_compare){
    return (game_name == game_name_to_compare);
}

bool Game::delete_player(int32_t& player_id){
    return protected_outputs_queue.delete_player(player_id);
}

bool Game::is_empty(){
    if (protected_outputs_queue.number_of_players() == 0){
        stop_playing();
        return true;
    }
    return false;
}

void Game::stop_playing(){
    keep_playing = false;
}

int32_t Game::get_game_code(){
    return code;
}

bool Game::can_join() {
    return (admit_players && protected_outputs_queue.number_of_players() < game_players);
}

bool Game::is_not_playing() {
    return keep_playing;
}
