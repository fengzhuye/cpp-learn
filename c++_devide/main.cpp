#include <iostream>
#include <cmath>

int main()
{
	const double pi = 3.14;
	double d1 = 2.1212;
 	double d2 = -5.1515;
	double d3 = 9.1919;
	double d4 = -9.999;
	int k1 = d1/(2*pi);
	int k2 = d2/(2*pi);
	int k3 = d3/(2*pi);
	int k4 = d4/(2*pi);
	double tail1 = d1%(2*pi);
	double tail2 = d2%(2*pi);
	double tail3 = d3%(2*pi);
	std::cerr << "k_1: " << k1 << std::endl;
	std::cerr << "k_2: " << k2 << std::endl;
	std::cerr << "k_3: " << k3 << std::endl;
	std::cerr << "k_3: " << k4 << std::endl;
	std::cerr << "tail1: " << tail1 << std::endl;
	std::cerr << "tail2: " << tail2 << std::endl;
	return 0;
}
