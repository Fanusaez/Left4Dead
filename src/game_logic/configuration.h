#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <yaml-cpp/yaml.h>

class Configuration {

private:
    const std::int16_t  soldier_health;

    std::int16_t  infected_health;
    std::int16_t  infected_damage;

    std::int16_t  jumper_health;
    std::int16_t  jumper_damage;

    std::int16_t  witch_health;
    std::int16_t  witch_damage;



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
};


#endif  // CONFIGURATION_H_
