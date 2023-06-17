#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <yaml-cpp/yaml.h>

class Configuration {

private:
    const std::int16_t  soldier_health;

    std::int16_t infected_health;
    std::int16_t infected_damage;

    std::int16_t jumper_health;
    std::int16_t jumper_damage;

    std::int16_t witch_health;
    std::int16_t witch_damage;
    std::int16_t witch_prob_scream;
    std::int16_t witch_zombies_created_for_scream;

    std::int16_t spear_health;
    std::int16_t spear_damage;

    float zombieState_time_attacking;
    float zombieState_time_jumping=1;
    float zombieState_time_running=1;
    float zombieState_time_screaming=1;
    float zombieState_time_stunned=1;
    float zombieState_time_walking=1;
    float zombieState_time_being_attacked=1;


    Configuration(const YAML::Node& node);
    void parse_configurations(const YAML::Node& configNode);

    ~Configuration();

public:

    static Configuration& getInstance();

    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    std::int16_t get_soldier_health();

    std::int16_t get_infected_health();
    std::int16_t get_infected_damage();

    std::int16_t get_jumper_health();
    std::int16_t get_jumper_damage();

    std::int16_t get_witch_health();
    std::int16_t get_witch_damage();
    std::int16_t get_witch_prob_scream();
    std::int16_t get_witch_zombies_created_screaming();

    std::int16_t get_spear_health();
    std::int16_t get_spear_damage();

    float get_zombieState_attacking_time();
    float get_zombieState_jumping_time();
    float get_zombieState_running_time();
    float get_zombieState_screaming_time();
    float get_zombieState_stunned_time();
    float get_zombieState_walking_time();
    float get_zombieState_being_attacked_time();
};


#endif  // CONFIGURATION_H_
