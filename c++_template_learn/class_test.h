#ifndef __CALSS_TEST__
#define __CALSS_TEST__

#include <iostream>
class Test
{
	Test()
	{
		std::cout << "Construct!!" << std::endl;
	}
	static void puts();
};

#endif