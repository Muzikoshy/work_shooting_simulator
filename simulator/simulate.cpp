//
// Created by Muzikosh on 22.07.2025.
//
#include "simulate.hpp"

#include <iostream>

#include "glm/ext/scalar_constants.hpp"

void Simulation::addShot(glm::vec3 shooter, glm::vec3 target, float velocity, float mass, float dt)
{
    auto entity = registry.create(); //create entity

    //set entity's values
    registry.emplace<shooterPos>(entity, shooter);
    registry.emplace<targetPos>(entity, target);
    registry.emplace<muzzleVel>(entity, velocity);
    registry.emplace<shotMass>(entity, mass);
    registry.emplace<timeStep>(entity, dt);
}

std::vector<float> Simulation::runAll() //simulate
{
    std::vector<float> results;

    auto view = registry.view<shooterPos, targetPos, muzzleVel, shotMass, timeStep>(); //get all entities

    for (auto entity : view) //loop through single entities
    {
        //get values of entity
        const auto& shooter = view.get<shooterPos>(entity).value;
        const auto& target  = view.get<targetPos>(entity).value;
        float velocity      = view.get<muzzleVel>(entity).value;
        float mass          = view.get<shotMass>(entity).value;
        float dt            = view.get<timeStep>(entity).value;

        bool hit = false;
        for (float angle = 0.0f /*should be 0.000...1f but should work just fine*/; angle < glm::radians(90.0f); angle += glm::radians(0.5f))
        {
            glm::vec3 dir = glm::normalize(target - shooter); //direction to target in unit vector
            dir.y = std::tan(angle); //get y/x based on current angle

            glm::vec3 vel = glm::normalize(dir) * velocity; //convert again in unit vector and calc init speed vector
            glm::vec3 pos = shooter; //init default pos of shot

            while (!hit && pos.y >= 0.f)
            {
                glm::vec3 gravityAcc(0, -gravity, 0); //calc and then apply gravity

                float _ρ = 1.205f; //common air density at 20 degrees and common altitude https://www.tzb-info.cz/tabulky-a-vypocty/70-hustota-sucheho-vzduchu
                float _C = 0.47f; //resistence factor for sphere https://cs.wikipedia.org/wiki/%C4%8Cinitel_odporu
                float _r = 0.0045f; // 4,5 mm (common 9mm ammo)
                float _S = glm::pi<float>() * glm::pow(_r, 2); //pi*r^2

                //(for vector shape) Fd = -1/2 * C * ρ * S * v^2 (=|v| * v)
                glm::vec3 envResist = -0.5f * _C * _ρ * _S * glm::length(vel) * vel;

                glm::vec3 envAcc = envResist / mass; //a = f/m

                glm::vec3 acc = gravityAcc + envAcc; //full acceleration

                vel += acc * dt; //calc new velocity
                pos += vel * dt; //calc new position

                if (pos.y < 0.f) //if we hit the ground, end
                    break;

                if (glm::distance(pos, target) <= 1.f) //we can make some tolerancy (based on size of target which is not implemented)
                {
                    std::cout << "DEBUG: distance: " << glm::distance(pos, target) << std::endl;
                    results.push_back(glm::degrees(angle)); //we hit, so save result and break for next entity
                    hit = true;
                    break;
                }
            }

            if (hit) //we just hit, break the second loop to move for next entity
                break;
        }

        if (!hit) //if we didnt hit, save -1.f angle (fail)
            results.push_back(-1.f);
    }

    return results;
}