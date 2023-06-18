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
                            soldierState_time_being_attacked(node["soldierStates"]["time_being_attacked"].as<float>()),
                            soldierState_time_calling_air_strike(node["soldierStates"]["time_calling_air_strike"].as<float>()),
                            soldierState_time_moving(node["soldierStates"]["time_moving"].as<float>()),
                            soldierState_time_reloading(node["soldierStates"]["time_reloading"].as<float>()),
                            soldierState_time_shooting(node["soldierStates"]["time_shooting"].as<float>()),
                            soldierState_time_throwing_explosive_g(node["soldierStates"]["time_throwing_explosive_g"].as<float>()),
                            soldierState_time_throwing_smoke_g(node["soldierStates"]["time_throwing_smoke_g"].as<float>()),
                            weaponIdf_mag_capacity(node["weapons"]["idf"]["mag_capacity"].as<std::int16_t>()),
                            weaponIdf_close_range_damage(node["weapons"]["idf"]["close_range_damage"].as<std::int16_t>()),
                            weaponIdf_long_range_damage(node["weapons"]["idf"]["long_range_damage"].as<std::int16_t>()),
                            weaponP90_mag_capacity(node["weapons"]["p90"]["mag_capacity"].as<std::int16_t>()),
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
                            jumper_health(node["jumper"]["health"].as<std::int16_t>()),
                            jumper_damage(node["jumper"]["damage"].as<std::int16_t>()),
                            witch_health(node["witch"]["health"].as<std::int16_t>()),
                            witch_damage(node["witch"]["damage"].as<std::int16_t>()),
                            witch_prob_scream(node["witch"]["probability_scream"].as<std::int16_t>()),
                            witch_zombies_created_for_scream(node["witch"]["zombies_created_for_screaming"].as<std::int16_t>()),
                            spear_health(node["spear"]["health"].as<std::int16_t>()),
                            spear_damage(node["spear"]["damage"].as<std::int16_t>()),
                            zombieState_time_attacking(node["zombieStates"]["time_attacking"].as<float>()),
                            zombieState_time_jumping(node["zombieStates"]["time_jumping"].as<float>()),
                            zombieState_time_running(node["zombieStates"]["time_running"].as<float>()),
                            zombieState_time_screaming(node["zombieStates"]["time_screaming"].as<float>()),
                            zombieState_time_stunned(node["zombieStates"]["time_stunned"].as<float>()),
                            zombieState_time_walking(node["zombieStates"]["time_walking"].as<float>()),
                            zombieState_time_being_attacked(node["zombieStates"]["time_being_attacked"].as<float>()) {}

std::int16_t Configuration::get_soldier_health() {
    return soldier_health;
}

std::int16_t Configuration::get_soldier_grenade_distance_reach() {
    return soldierGrenade_distance_reach;
}

float Configuration::get_soldierState_time_being_attacked() {
    return soldierState_time_being_attacked;
}

float Configuration::get_soldierState_time_calling_air_strike() {
    return soldierState_time_calling_air_strike;
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

std::int16_t Configuration::get_weaponIdf_close_range_damage() {
    return weaponIdf_close_range_damage;
}

std::int16_t Configuration::get_weaponIdf_long_range_damage() {
    return weaponIdf_long_range_damage;
}

std::int16_t Configuration::get_weaponP90_mag_capacity() {
    return weaponP90_mag_capacity;
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

std::int16_t Configuration::get_jumper_health() {
    return jumper_health;
}

std::int16_t Configuration::get_jumper_damage() {
    return jumper_damage;
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

std::int16_t Configuration::get_spear_health() {
    return spear_health;
}

std::int16_t Configuration::get_spear_damage() {
    return spear_damage;
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

Configuration::~Configuration() {}