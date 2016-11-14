
#include "car.hpp"
Car::Car(int numCylinders):Engine(numCylinders)
{
    std::cout << "car costruct: " << numCylinders << " cylinders" << std::endl;
}
//void Car::start(int numCylinders)
//{
//    std::cout << "car start" << std::endl;
//}
