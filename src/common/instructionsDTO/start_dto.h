#ifndef STARTDTO_H
#define STARTDTO_H

#include "instructions_dto.h"
#include <stdint.h>

class StartDTO : public InstructionsDTO {
private:
    bool could_start;

public:
    StartDTO();

    explicit StartDTO(bool could_join); 

    bool get_could_start();
};
#endif
