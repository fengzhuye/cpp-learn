
#include "engine.hpp"
Engine::Engine(int numCylinders)
{
c = numCylinders;
    std::cout << "engine costruct: " << numCylinders << " cylinders" << std::endl;
}
void Engine::start()
{
    std::cout << "engine start: " <<  c << std::endl;
}
