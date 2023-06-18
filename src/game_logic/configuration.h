#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <yaml-cpp/yaml.h>

class Configuration {

private:
    std::int16_t  soldier_health;

    float soldierState_time_being_attacked;
    float soldierState_time_calling_air_strike;
    float soldierState_time_moving;
    float soldierState_time_reloading;
    float soldierState_time_shooting;
    float soldierState_time_throwing_explosive_g;
    float soldierState_time_throwing_smoke_g;

    std::int16_t weaponIdf_mag_capacity;
    std::int16_t weaponIdf_close_range_damage;
    std::int16_t weaponIdf_long_range_damage;

    std::int16_t weaponP90_mag_capacity;
    std::int16_t weaponP90_damage;

    std::int16_t weaponScout_mag_capacity;
    std::int16_t weaponScout_damage;
    std::int16_t weaponScout_damage_reduction_per_hit;

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
    float zombieState_time_jumping;
    float zombieState_time_running;
    float zombieState_time_screaming;
    float zombieState_time_stunned;
    float zombieState_time_walking;
    float zombieState_time_being_attacked;


    Configuration(const YAML::Node& node);
    void parse_configurations(const YAML::Node& configNode);

    ~Configuration();

public:

    static Configuration& getInstance();

    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    std::int16_t get_soldier_health();

    float get_soldierState_time_being_attacked();
    float get_soldierState_time_calling_air_strike();
    float get_soldierState_time_moving();
    float get_soldierState_time_reloading();
    float get_soldierState_time_shooting();
    float get_soldierState_time_throwing_explosive_grenade();
    float get_soldierState_time_throwing_smoke_grenade();

    std::int16_t get_weaponIdf_mag_capacity();
    std::int16_t get_weaponIdf_close_range_damage();
    std::int16_t get_weaponIdf_long_range_damage();
    std::int16_t get_weaponP90_mag_capacity();
    std::int16_t get_weaponP90_damage();
    std::int16_t get_weaponScout_mag_capacity();
    std::int16_t get_weaponScout_damage();
    std::int16_t get_weaponScout_reduction_per_hit();

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
