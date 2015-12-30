#include <iostream>
#include "foo.hpp"

int FOO_BAR::func()
{
	return 7;
};

int main()
{
	FOO_BAR t;
	t.a = 12;
	std::cout << t.a*2 << std::endl;
	std::cout << t.func() << std::endl;

}
