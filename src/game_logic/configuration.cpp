#include "configuration.h"
#include <fstream>
#include <iostream>

Configuration& Configuration::getInstance() {
    static Configuration instance(YAML::LoadFile("../configurations.yaml"));
    return instance;
}

Configuration::Configuration(const YAML::Node& node) :
                            soldier_health(node["soldier"]["health"].as<std::int16_t>()),
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