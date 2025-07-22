//
// Created by Muzikosh on 22.07.2025.
//

#ifndef ENTT_COMPONENTS_HPP
#define ENTT_COMPONENTS_HPP
#include <glm/glm.hpp>

struct shooterPos //3D shooter location
{
    glm::vec3 value;
};

struct targetPos //3D target location
{
    glm::vec3 value;
};

struct muzzleVel //muzzle velocity of shot
{
    float value;
};

struct shotMass //mass of shot
{
    float value;
};

struct timeStep //time step of simulation
{
    float value;
};
#endif //ENTT_COMPONENTS_HPP
