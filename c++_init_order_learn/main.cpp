#include <iostream>
#include <cmath>


class X
{
public:
	int i;
	int j;
public:
	X(int val):j(val),i(j)
	{
	
	}
};

int main()
{
	X a(6);
        std::cerr << "a.i: " << a.i << std::endl;
	std::cerr << "a.j: " << a.j << std::endl;
}
