#include <iostream>

struct  _data  
{  
  unsigned int a:3;  
  char b:3;
  char c:1;  
};

int main()
{

 _data data;
data.a = 9;
std::cout << data.a << std::endl;
return 0;

}
