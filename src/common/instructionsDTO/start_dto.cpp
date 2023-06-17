#include "start_dto.h"

StartDTO::StartDTO() : InstructionsDTO(START),could_start(false){} 

StartDTO::StartDTO(bool could_start) : InstructionsDTO(START), could_start(could_start){} 

bool StartDTO::get_could_start() {return could_start;}
