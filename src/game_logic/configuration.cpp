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
                            witch_damage(node["witch"]["damage"].as<std::int16_t>()) {}


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


Configuration::~Configuration() {}