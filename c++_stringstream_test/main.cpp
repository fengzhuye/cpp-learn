#include <iostream>
#include <string>
#include <sstream>

int main()
{
	int i = 7;
	double d = 1.234;
	char c = 'A';
	std::string s = "hello";
	char* pchar = "world";

	std::stringstream p;
	p << i;
	p << d;
	p << c;
	p << s;
	p << pchar;
	std::string p_start = "p";
	p_start += p.str();
	std::cout << p_start << std::endl;
	
}

