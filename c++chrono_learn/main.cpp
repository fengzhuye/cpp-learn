// Example program
#include <iostream>
#include <string>
#include <chrono>

int main()
{
  std::string name;
  std::cout << "What is your name? ";
  getline (std::cin, name);
  std::cout << "Hello, " << name << "!\n";
  
  std::chrono::seconds dur(static_cast<int>(0.234*10));  //milliseconds
  std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
  while(std::chrono::high_resolution_clock::now() < current+dur)
  {
  }
  std::cout << "END>>>>" << std::endl;
  
}

