#include <iostream>
#include <exception>
#include <vector>
//using namespace std;

// see links: 
// http://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4079/Allocators-STL.htm
// http://www.codeproject.com/Articles/4795/C-Standard-Allocator-An-Introduction-and-Implement

class Test
{
public:
	Test()
	{
		std::cout << "Constructor" << std::endl;
	}	
	~Test()
	{
		std::cout << "DDDConstructor" << std::endl;
	}
	Test(const Test& p) 
	{ 
  		std::cout << "Copy Constructor" <<  std::endl; 
  	} 	
  	Test(const Test&& p) 
	{ 
  		std::cout << "Move Constructor" <<  std::endl; 
  	} 
    Test& operator=(const Test& str) 
    { 
	    std::cout << "Copy Assignment"  << std::endl; 
	    return *this; 
	}
	Test& operator=(const Test&&) 
    { 
	    std::cout << "Move Assignment"  << std::endl; 
	    return *this; 
	}
};

std::vector<int> test_function()
{
	return {1,2,3};
}
 
int main()
{
	void * a = ::operator new(sizeof(Test));
	std::cout << "address: " << a << std::endl;
	::operator delete(a);
	std::cout << "address: " << a << std::endl;
	 //std::cout << v() << " " << std::endl;

	return 0;

}
