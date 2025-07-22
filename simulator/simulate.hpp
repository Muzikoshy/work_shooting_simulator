//
// Created by Muzikosh on 22.07.2025.
//

#ifndef SIMULATE_HPP
#define SIMULATE_HPP
#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include "entt_components.hpp"

class Simulation
{
public:
    void addShot(glm::vec3 shooter, glm::vec3 target, float velocity, float mass, float dt);
    std::vector<float> runAll();

private:
    entt::registry registry;
    static constexpr float gravity = 9.81f;
};

#endif //SIMULATE_HPP
