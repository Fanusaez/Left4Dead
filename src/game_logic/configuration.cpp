#include "configuration.h"
#include <fstream>
#include <iostream>

Configuration& Configuration::getInstance() {
    static Configuration instance(YAML::LoadFile("../configurations.yaml"));
    return instance;
}

Configuration::Configuration(const YAML::Node& node) :
                            soldier_health(node["soldier"]["health"].as<std::int16_t>()),
                            soldierGrenade_distance_reach(node["soldier"]["grenade_distance_reach"].as<std::int16_t>()),
                            soldier_matrix_range_to_revive(node["soldier"]["matrix_range_to_revive"].as<std::int16_t>()),
                            soldierState_time_being_attacked(node["soldierStates"]["time_being_attacked"].as<float>()),
                            soldierState_time_calling_air_strike(node["soldierStates"]["time_calling_air_strike"].as<float>()),
                            soldierState_time_permanent_dead(node["soldierStates"]["time_permanent_dead"].as<float>()),
                            soldierState_time_moving(node["soldierStates"]["time_moving"].as<float>()),
                            soldierState_time_reloading(node["soldierStates"]["time_reloading"].as<float>()),
                            soldierState_time_shooting(node["soldierStates"]["time_shooting"].as<float>()),
                            soldierState_time_throwing_explosive_g(node["soldierStates"]["time_throwing_explosive_g"].as<float>()),
                            soldierState_time_throwing_smoke_g(node["soldierStates"]["time_throwing_smoke_g"].as<float>()),
                            weaponIdf_mag_capacity(node["weapons"]["idf"]["mag_capacity"].as<std::int16_t>()),
                            weaponIdf_burst_capacity(node["weapons"]["idf"]["burst_capacity"].as<std::int16_t>()),
                            weaponIdf_close_range_damage(node["weapons"]["idf"]["close_range_damage"].as<std::int16_t>()),
                            weaponIdf_long_range_damage(node["weapons"]["idf"]["long_range_damage"].as<std::int16_t>()),
                            weaponIdf_matrix_range_to_reduce_damage(node["weapons"]["idf"]["matrix_range_to_reduce_damage"].as<std::int16_t>()),
                            weaponP90_mag_capacity(node["weapons"]["p90"]["mag_capacity"].as<std::int16_t>()),
                            weaponP90_burst_capacity(node["weapons"]["p90"]["burst_capacity"].as<std::int16_t>()),
                            weaponP90_damage(node["weapons"]["p90"]["damage"].as<std::int16_t>()),
                            weaponScout_mag_capacity(node["weapons"]["scout"]["mag_capacity"].as<std::int16_t>()),
                            weaponScout_damage(node["weapons"]["scout"]["damage"].as<std::int16_t>()),
                            weaponScout_damage_reduction_per_hit(node["weapons"]["scout"]["damage_reduction_per_hit"].as<std::int16_t>()),
                            explosiveGrenade_damage(node["explosiveGrenade"]["damage"].as<std::int16_t>()),
                            explosiveGrenade_time_to_reThrow(node["explosiveGrenade"]["time_to_reThrow_grenade"].as<std::int16_t>()),
                            explosiveGrenade_radius_range(node["explosiveGrenade"]["radius_range"].as<std::int16_t>()),
                            smokeGrenade_time_to_reThrow(node["smokeGrenade"]["time_to_reThrow_grenade"].as<std::int16_t>()),
                            smokeGrenade_radius_range(node["smokeGrenade"]["radius_range"].as<std::int16_t>()),
                            grenadeState_time_exploding(node["grenadeStates"]["time_exploding"].as<float>()),
                            grenadeState_time_thrown_grenade(node["grenadeStates"]["time_thrown_grenade"].as<float>()),
                            infected_health(node["infected"]["health"].as<std::int16_t>()),
                            infected_damage(node["infected"]["damage"].as<std::int16_t>()),
                            infected_distance_to_hit(node["infected"]["distance_to_hit"].as<std::int16_t>()),
                            infected_sight_distance(node["infected"]["sight_distance"].as<std::int16_t>()),
                            infected_prob_walk(node["infected"]["probability_walk"].as<std::vector<std::int16_t>>()),
                            infected_prob_run(node["infected"]["probability_run"].as<std::vector<std::int16_t>>()),
                            infected_prob_jump(node["infected"]["probability_jump"].as<std::vector<std::int16_t>>()),
                            jumper_health(node["jumper"]["health"].as<std::int16_t>()),
                            jumper_damage(node["jumper"]["damage"].as<std::int16_t>()),
                            jumper_distance_to_hit(node["jumper"]["distance_to_hit"].as<std::int16_t>()),
                            jumper_sight_distance(node["jumper"]["sight_distance"].as<std::int16_t>()),
                            jumper_prob_walk(node["jumper"]["probability_walk"].as<std::vector<std::int16_t>>()),
                            jumper_prob_run(node["jumper"]["probability_run"].as<std::vector<std::int16_t>>()),
                            jumper_prob_jump(node["jumper"]["probability_jump"].as<std::vector<std::int16_t>>()),
                            witch_health(node["witch"]["health"].as<std::int16_t>()),
                            witch_damage(node["witch"]["damage"].as<std::int16_t>()),
                            witch_prob_scream(node["witch"]["probability_scream"].as<std::int16_t>()),
                            witch_zombies_created_for_scream(node["witch"]["zombies_created_for_screaming"].as<std::int16_t>()),
                            witch_distance_to_hit(node["witch"]["distance_to_hit"].as<std::int16_t>()),
                            witch_sight_distance(node["witch"]["sight_distance"].as<std::int16_t>()),
                            witch_prob_walk(node["witch"]["probability_walk"].as<std::vector<std::int16_t>>()),
                            witch_prob_run(node["witch"]["probability_run"].as<std::vector<std::int16_t>>()),
                            witch_prob_jump(node["witch"]["probability_jump"].as<std::vector<std::int16_t>>()),
                            spear_health(node["spear"]["health"].as<std::int16_t>()),
                            spear_damage(node["spear"]["damage"].as<std::int16_t>()),
                            spear_distance_to_hit(node["spear"]["distance_to_hit"].as<std::int16_t>()),
                            spear_sight_distance(node["spear"]["sight_distance"].as<std::int16_t>()),
                            spear_prob_walk(node["spear"]["probability_walk"].as<std::vector<std::int16_t>>()),
                            spear_prob_run(node["spear"]["probability_run"].as<std::vector<std::int16_t>>()),
                            spear_prob_jump(node["spear"]["probability_jump"].as<std::vector<std::int16_t>>()),
                            venom_health(node["venom"]["health"].as<std::int16_t>()),
                            venom_close_range_damage(node["venom"]["damage_close_range"].as<std::int16_t>()),
                            venom_long_range_damage(node["venom"]["damage_long_range"].as<std::int16_t>()),
                            venom_distance_to_hit_close_range(node["venom"]["distance_to_hit_close_range"].as<std::int16_t>()),
                            venom_distance_to_hit_long_range(node["venom"]["distance_to_hit_long_range"].as<std::int16_t>()),
                            venom_sight_distance(node["venom"]["sight_distance"].as<std::int16_t>()),
                            venom_prob_walk(node["venom"]["probability_walk"].as<std::vector<std::int16_t>>()),
                            venom_prob_run(node["venom"]["probability_run"].as<std::vector<std::int16_t>>()),
                            venom_prob_jump(node["venom"]["probability_jump"].as<std::vector<std::int16_t>>()),
                            zombieState_time_attacking(node["zombieStates"]["time_attacking"].as<float>()),
                            zombieState_time_jumping(node["zombieStates"]["time_jumping"].as<float>()),
                            zombieState_time_running(node["zombieStates"]["time_running"].as<float>()),
                            zombieState_time_screaming(node["zombieStates"]["time_screaming"].as<float>()),
                            zombieState_time_stunned(node["zombieStates"]["time_stunned"].as<float>()),
                            zombieState_time_walking(node["zombieStates"]["time_walking"].as<float>()),
                            zombieState_time_being_attacked(node["zombieStates"]["time_being_attacked"].as<float>()),
                            matrix_movements_per_cell(node["mapLogic"]["matrix_movements_per_cell"].as<std::int16_t>()),
                            CTZ_time_respawn_zombies(node["clearTheZone"]["time_respawn_zombies"].as<std::int16_t>()),
                            CTZ_total_quantity_zombies(node["clearTheZone"]["total_quantity_zombies"].as<std::int16_t>()),
                            CTZ_infected_prob_respawn(node["clearTheZone"]["zombies_probability_respawn"]["infected"].as<std::vector<std::int16_t>>()),
                            CTZ_witch_prob_respawn(node["clearTheZone"]["zombies_probability_respawn"]["witch"].as<std::vector<std::int16_t>>()),
                            CTZ_jumper_prob_respawn(node["clearTheZone"]["zombies_probability_respawn"]["jumper"].as<std::vector<std::int16_t>>()),
                            CTZ_spear_prob_respawn(node["clearTheZone"]["zombies_probability_respawn"]["spear"].as<std::vector<std::int16_t>>()),
                            CTZ_venom_prob_respawn(node["clearTheZone"]["zombies_probability_respawn"]["venom"].as<std::vector<std::int16_t>>()),
                            survival_time_respawn_zombies(node["survival"]["time_respawn_zombies"].as<std::int16_t>()),
                            survival_time_zombies_getting_stronger(node["survival"]["time_zombies_getting_stronger"].as<std::int16_t>()),
                            survival_zombies_health_power_up(node["survival"]["health_power_up"].as<std::int16_t>()),
                            survival_zombies_damage_power_up(node["survival"]["damage_power_up"].as<std::int16_t>()),
                            survival_infected_prob_respawn(node["survival"]["zombies_probability_respawn"]["infected"].as<std::vector<std::int16_t>>()),
                            survival_witch_prob_respawn(node["survival"]["zombies_probability_respawn"]["witch"].as<std::vector<std::int16_t>>()),
                            survival_jumper_prob_respawn(node["survival"]["zombies_probability_respawn"]["jumper"].as<std::vector<std::int16_t>>()),
                            survival_spear_prob_respawn(node["survival"]["zombies_probability_respawn"]["spear"].as<std::vector<std::int16_t>>()),
                            survival_venom_prob_respawn(node["survival"]["zombies_probability_respawn"]["venom"].as<std::vector<std::int16_t>>()),
                            GF_infected_prob_respawn(node["gameFactory"]["zombies_probability_respawn"]["infected"].as<std::vector<std::int16_t>>()),
                            GF_witch_prob_respawn(node["gameFactory"]["zombies_probability_respawn"]["witch"].as<std::vector<std::int16_t>>()),
                            GF_jumper_prob_respawn(node["gameFactory"]["zombies_probability_respawn"]["jumper"].as<std::vector<std::int16_t>>()),
                            GF_spear_prob_respawn(node["gameFactory"]["zombies_probability_respawn"]["spear"].as<std::vector<std::int16_t>>()),
                            GF_venom_prob_respawn(node["gameFactory"]["zombies_probability_respawn"]["venom"].as<std::vector<std::int16_t>>()),
                            air_strike_radius_range_safe_space(node["airStrike"]["radius_range_safe_space"].as<std::int16_t>()),
                            air_strike_damage(node["airStrike"]["damage"].as<std::int16_t>()),
                            air_strike_time_to_reCall(node["airStrike"]["time_reCall_air_strike"].as<std::int16_t>()),
                            air_strike_state_exploding(node["airStrikeStates"]["time_exploding"].as<float>()),
                            air_strike_state_incoming(node["airStrikeStates"]["time_incoming"].as<float>()) {}

std::int16_t Configuration::get_soldier_health() {
    return soldier_health;
}

std::int16_t Configuration::get_soldier_grenade_distance_reach() {
    return soldierGrenade_distance_reach;
}

std::int16_t Configuration::get_soldier_matrix_range_to_revive() {
    return soldier_matrix_range_to_revive;
}

float Configuration::get_soldierState_time_being_attacked() {
    return soldierState_time_being_attacked;
}

float Configuration::get_soldierState_time_calling_air_strike() {
    return soldierState_time_calling_air_strike;
}

float Configuration::get_soldierState_time_permanent_dead() {
    return soldierState_time_permanent_dead;
}

float Configuration::get_soldierState_time_moving() {
    return soldierState_time_moving;
}

float Configuration::get_soldierState_time_reloading() {
    return soldierState_time_reloading;
}

float Configuration::get_soldierState_time_shooting() {
    return soldierState_time_shooting;
}

float Configuration::get_soldierState_time_throwing_explosive_grenade() {
    return soldierState_time_throwing_explosive_g;
}

float Configuration::get_soldierState_time_throwing_smoke_grenade() {
    return soldierState_time_throwing_smoke_g;
}

std::int16_t Configuration::get_weaponIdf_mag_capacity() {
    return weaponIdf_mag_capacity;
}

std::int16_t Configuration::get_weaponIdf_burst_capacity() {
    return weaponIdf_burst_capacity;
}

std::int16_t Configuration::get_weaponIdf_close_range_damage() {
    return weaponIdf_close_range_damage;
}

std::int16_t Configuration::get_weaponIdf_long_range_damage() {
    return weaponIdf_long_range_damage;
}

std::int16_t Configuration::get_weaponIdf_matrix_range_to_reduce_damage() {
    return weaponIdf_matrix_range_to_reduce_damage;
}

std::int16_t Configuration::get_weaponP90_mag_capacity() {
    return weaponP90_mag_capacity;
}

std::int16_t Configuration::get_weaponP90_burst_capacity() {
    return weaponP90_burst_capacity;
}

std::int16_t Configuration::get_weaponP90_damage() {
    return weaponP90_damage;
}

std::int16_t Configuration::get_weaponScout_mag_capacity() {
    return weaponScout_mag_capacity;
}

std::int16_t Configuration::get_weaponScout_damage() {
    return weaponScout_damage;
}

std::int16_t Configuration::get_weaponScout_reduction_per_hit() {
    return weaponScout_damage_reduction_per_hit;
}

std::int16_t Configuration::get_explosiveGrenade_damage() {
    return explosiveGrenade_damage;
}

std::int16_t Configuration::get_explosiveGrenade_time_to_reThrow() {
    return explosiveGrenade_time_to_reThrow;
}

std::int16_t Configuration::get_explosiveGrenade_radius_range() {
    return explosiveGrenade_radius_range;
}

std::int16_t Configuration::get_smokeGrenade_time_to_reThrow() {
    return smokeGrenade_time_to_reThrow;
}

std::int16_t Configuration::get_smokeGrenade_radius_range() {
    return smokeGrenade_radius_range;
}

float Configuration::get_grenadeState_time_exploding() {
    return grenadeState_time_exploding;
}

float Configuration::get_grenadeState_time_thrown_grenade() {
    return grenadeState_time_thrown_grenade;
}

std::int16_t Configuration::get_infected_health() {
    return infected_health;
}

std::int16_t Configuration::get_infected_damage() {
    return infected_damage;
}

std::int16_t Configuration::get_infected_distance_to_hit() {
    return infected_distance_to_hit;
}

std::int16_t Configuration::get_infected_sight_distance() {
    return infected_sight_distance;
}

std::vector<std::int16_t> Configuration::get_infected_prob_to_walk() {
    return infected_prob_walk;
}

std::vector<std::int16_t> Configuration::get_infected_prob_to_run() {
    return infected_prob_run;
}

std::vector<std::int16_t> Configuration::get_infected_prob_to_jump() {
    return infected_prob_jump;
}

std::int16_t Configuration::get_jumper_health() {
    return jumper_health;
}

std::int16_t Configuration::get_jumper_damage() {
    return jumper_damage;
}

std::int16_t Configuration::get_jumper_distance_to_hit() {
    return jumper_distance_to_hit;
}

std::int16_t Configuration::get_jumper_sight_distance() {
    return jumper_sight_distance;
}

std::vector<std::int16_t> Configuration::get_jumper_prob_to_walk() {
    return jumper_prob_walk;
}

std::vector<std::int16_t> Configuration::get_jumper_prob_to_run() {
    return jumper_prob_run;
}

std::vector<std::int16_t> Configuration::get_jumper_prob_to_jump() {
    return jumper_prob_jump;
}


std::int16_t Configuration::get_witch_health() {
    return witch_health;
}

std::int16_t Configuration::get_witch_damage() {
    return witch_damage;
}

std::int16_t Configuration::get_witch_prob_scream() {
    return witch_prob_scream;
}

std::int16_t Configuration::get_witch_zombies_created_screaming() {
    return witch_zombies_created_for_scream;
}

std::int16_t Configuration::get_witch_distance_to_hit() {
    return witch_distance_to_hit;
}

std::int16_t Configuration::get_witch_sight_distance() {
    return witch_sight_distance;
}

std::vector<std::int16_t> Configuration::get_witch_prob_to_walk() {
    return witch_prob_walk;
}

std::vector<std::int16_t> Configuration::get_witch_prob_to_run() {
    return witch_prob_run;
}

std::vector<std::int16_t> Configuration::get_witch_prob_to_jump() {
    return witch_prob_jump;
}


std::int16_t Configuration::get_spear_health() {
    return spear_health;
}

std::int16_t Configuration::get_spear_damage() {
    return spear_damage;
}

std::int16_t Configuration::get_spear_distance_to_hit() {
    return spear_distance_to_hit;
}

std::int16_t Configuration::get_spear_sight_distance() {
    return spear_sight_distance;
}

std::vector<std::int16_t> Configuration::get_spear_prob_to_walk() {
    return spear_prob_walk;
}

std::vector<std::int16_t> Configuration::get_spear_prob_to_run() {
    return spear_prob_run;
}

std::vector<std::int16_t> Configuration::get_spear_prob_to_jump() {
    return spear_prob_jump;
}


std::int16_t Configuration::get_venom_health() {
    return venom_health;
}

std::int16_t Configuration::get_venom_damage_close_range() {
    return venom_close_range_damage;
}

std::int16_t Configuration::get_venom_damage_long_range() {
    return venom_long_range_damage;
}

std::int16_t Configuration::get_venom_distance_to_hit_close_range() {
    return venom_distance_to_hit_close_range;
}

std::int16_t Configuration::get_venom_distance_to_hit_long_range() {
    return venom_distance_to_hit_long_range;
}

std::int16_t Configuration::get_venom_sight_distance() {
    return venom_sight_distance;
}

std::vector<std::int16_t> Configuration::get_venom_prob_to_walk() {
    return venom_prob_walk;
}

std::vector<std::int16_t> Configuration::get_venom_prob_to_run() {
    return venom_prob_run;
}

std::vector<std::int16_t> Configuration::get_venom_prob_to_jump() {
    return venom_prob_jump;
}


float Configuration::get_zombieState_attacking_time() {
    return zombieState_time_attacking;
}

float Configuration::get_zombieState_jumping_time() {
    return zombieState_time_jumping;
}

float Configuration::get_zombieState_running_time() {
    return zombieState_time_running;
}

float Configuration::get_zombieState_screaming_time() {
    return zombieState_time_screaming;
}

float Configuration::get_zombieState_stunned_time() {
    return zombieState_time_stunned;
}

float Configuration::get_zombieState_walking_time() {
    return zombieState_time_walking;
}

float Configuration::get_zombieState_being_attacked_time() {
    return zombieState_time_being_attacked;
}

std::int16_t Configuration::get_movements_per_cell() {
    return matrix_movements_per_cell;
}

std::int16_t Configuration::get_CTZ_time_respawn_zombies() {
    return CTZ_time_respawn_zombies;
}

std::int16_t Configuration::get_CTZ_total_quantity_zombies() {
    return CTZ_total_quantity_zombies;
}

std::vector<std::int16_t> Configuration::get_CTZ_infected_prob_to_respawn() {
    return CTZ_infected_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_CTZ_witch_prob_to_respawn() {
    return CTZ_witch_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_CTZ_jumper_prob_to_respawn() {
    return CTZ_jumper_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_CTZ_spear_prob_to_respawn() {
    return CTZ_spear_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_CTZ_venom_prob_to_respawn() {
    return CTZ_venom_prob_respawn;
}

std::int16_t Configuration::get_survival_time_respawn_zombies() {
    return survival_time_respawn_zombies;
}

std::int16_t Configuration::get_survival_time_zombies_getting_stronger() {
    return survival_time_zombies_getting_stronger;
}

std::int16_t Configuration::get_survival_health_power_up() {
    return survival_zombies_health_power_up;
}

std::int16_t Configuration::get_survival_damage_power_up() {
    return survival_zombies_damage_power_up;
}

std::vector<std::int16_t> Configuration::get_survival_infected_prob_to_respawn() {
    return survival_infected_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_survival_witch_prob_to_respawn() {
    return survival_witch_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_survival_jumper_prob_to_respawn() {
    return survival_jumper_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_survival_spear_prob_to_respawn() {
    return survival_spear_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_survival_venom_prob_to_respawn() {
    return survival_venom_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_GF_infected_prob_to_respawn() {
    return GF_infected_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_GF_witch_prob_to_respawn() {
    return GF_witch_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_GF_jumper_prob_to_respawn() {
    return GF_jumper_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_GF_spear_prob_to_respawn() {
    return GF_spear_prob_respawn;
}

std::vector<std::int16_t> Configuration::get_GF_venom_prob_to_respawn() {
    return GF_venom_prob_respawn;
}

std::int16_t Configuration::get_air_strike_radius_range_safe_space() {
    return air_strike_radius_range_safe_space;
}

std::int16_t Configuration::get_air_strike_damage() {
    return air_strike_damage;
}

std::int16_t Configuration::get_air_strike_time_reCall() {
    return air_strike_time_to_reCall;
}

float Configuration::get_air_strike_state_time_exploding() {
    return air_strike_state_exploding;
}

float Configuration::get_air_strike_state_time_incoming() {
    return air_strike_state_incoming;
}

Configuration::~Configuration() {}