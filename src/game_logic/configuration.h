#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <yaml-cpp/yaml.h>

class Configuration {

private:
    std::int16_t  soldier_health;
    std::int16_t  soldierGrenade_distance_reach;

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

    std::int16_t explosiveGrenade_damage;
    std::int16_t explosiveGrenade_time_to_reThrow;
    std::int16_t explosiveGrenade_radius_range;

    std::int16_t smokeGrenade_time_to_reThrow;
    std::int16_t smokeGrenade_radius_range;

    float grenadeState_time_exploding;
    float grenadeState_time_thrown_grenade;

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

    std::int16_t matrix_movements_per_cell;

    std::int16_t CTZ_time_respawn_zombies;
    std::int16_t CTZ_total_quantity_zombies;
    std::vector<std::int16_t> CTZ_infected_prob_respawn;
    std::vector<std::int16_t> CTZ_witch_prob_respawn;
    std::vector<std::int16_t> CTZ_jumper_prob_respawn;
    std::vector<std::int16_t> CTZ_spear_prob_respawn;
    std::vector<std::int16_t> CTZ_venom_prob_respawn;

    std::int16_t survival_time_respawn_zombies;
    std::int16_t survival_time_zombies_getting_stronger;
    std::int16_t survival_zombies_health_power_up;
    std::vector<std::int16_t> survival_infected_prob_respawn;
    std::vector<std::int16_t> survival_witch_prob_respawn;
    std::vector<std::int16_t> survival_jumper_prob_respawn;
    std::vector<std::int16_t> survival_spear_prob_respawn;
    std::vector<std::int16_t> survival_venom_prob_respawn;

    std::vector<std::int16_t> GF_infected_prob_respawn;
    std::vector<std::int16_t> GF_witch_prob_respawn;
    std::vector<std::int16_t> GF_jumper_prob_respawn;
    std::vector<std::int16_t> GF_spear_prob_respawn;
    std::vector<std::int16_t> GF_venom_prob_respawn;

    Configuration(const YAML::Node& node);
    void parse_configurations(const YAML::Node& configNode);

    ~Configuration();

public:

    static Configuration& getInstance();

    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    std::int16_t get_soldier_health();
    std::int16_t get_soldier_grenade_distance_reach();

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

    std::int16_t get_explosiveGrenade_damage();
    std::int16_t get_explosiveGrenade_time_to_reThrow();
    std::int16_t get_explosiveGrenade_radius_range();

    std::int16_t get_smokeGrenade_time_to_reThrow();
    std::int16_t get_smokeGrenade_radius_range();

    float get_grenadeState_time_exploding();
    float get_grenadeState_time_thrown_grenade();

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

    std::int16_t get_movements_per_cell();

    std::int16_t get_CTZ_time_respawn_zombies();
    std::int16_t get_CTZ_total_quantity_zombies();
    std::vector<std::int16_t> get_CTZ_infected_prob_to_respawn();
    std::vector<std::int16_t> get_CTZ_witch_prob_to_respawn();
    std::vector<std::int16_t> get_CTZ_jumper_prob_to_respawn();
    std::vector<std::int16_t> get_CTZ_spear_prob_to_respawn();
    std::vector<std::int16_t> get_CTZ_venom_prob_to_respawn();

    std::int16_t get_survival_time_respawn_zombies();
    std::int16_t get_survival_time_zombies_getting_stronger();
    std::int16_t get_survival_health_power_up();
    std::vector<std::int16_t> get_survival_infected_prob_to_respawn();
    std::vector<std::int16_t> get_survival_witch_prob_to_respawn();
    std::vector<std::int16_t> get_survival_jumper_prob_to_respawn();
    std::vector<std::int16_t> get_survival_spear_prob_to_respawn();
    std::vector<std::int16_t> get_survival_venom_prob_to_respawn();

    std::vector<std::int16_t> get_GF_infected_prob_to_respawn();
    std::vector<std::int16_t> get_GF_witch_prob_to_respawn();
    std::vector<std::int16_t> get_GF_jumper_prob_to_respawn();
    std::vector<std::int16_t> get_GF_spear_prob_to_respawn();
    std::vector<std::int16_t> get_GF_venom_prob_to_respawn();
};


#endif  // CONFIGURATION_H_