#include <iostream>

int (*functionPtr)(int, int);

int addInt(int n,int m)
{
	return n+m;
}
// int add2to3(int (*funcPtr)(int,int))
// {
// 	return funcPtr(2,3);
// }

int (&functionFactoryRef)(int, int)= addInt;
int (*(*functionFactoryPtr)(int n))(int, int);

int (*(functionFactory)(int n))(int, int)
{
    std::cout << "Got parameter" <<  n << std::endl;
    int (*functionPtr)(int,int) = &addInt;
    return functionPtr;
}

int main()
{
	//functionFactoryRef = &addInt;
	//functionPtr = &addInt;
	std::cout << functionFactoryRef(4,7) << std::endl;
	// functionFactoryRef = addInt;
	// functionFactoryPtr = @functionFactory;
	// std::cout << add2to3(functionPtr) << std::endl;
	std::cout << (******(*****functionFactory)(4))(3,6) << std::endl;

}