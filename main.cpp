#include <iostream>
#include "simulator/simulate.hpp"

int main()
{
    Simulation sim;

    sim.addShot({0, 0, 0}, {100, 10, 0}, 300.0f, 0.01f, 0.01f);
    sim.addShot({0, 0, 0}, {200, 50, 0}, 250.0f, 0.02f, 0.01f);
    sim.addShot({0, 0, 0}, {300, 100, 0}, 100.0f, 0.01f, 0.01f);
    sim.addShot({0, 0, 0}, {100, 5, 0}, 250.0f, 0.02f, 0.01f);
    sim.addShot({0, 0, 0}, {1, 0, 0}, 250.0f, 0.02f, 0.01f); //TODO fix calc logic (returning miss when target is 1m away)


    auto angles = sim.runAll();

    for (int i = static_cast<int>(angles.size()) - 1; i >= 0; --i)
    {
        std::cout << "Simulation number " << i + 1 << ": ";
        if (angles[i] >= 0.0f)
            std::cout << "Hit: " << angles[i] << " degrees\n";
        else
            std::cout << "Didn't hit.\n";
    }

    return 0;
}