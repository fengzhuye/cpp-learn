#ifndef Car_HPP_
#define Car_HPP_
#include <iostream>
#include "engine.hpp"
class Car:private Engine
{
public:
  Car(int numCylinders);
  using Engine::start;

  //void start();                 // Starts this Engine
};
#endif
