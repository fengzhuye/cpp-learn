#include <iostream>
#include <exception>
#include <vector>
//using namespace std;
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
	int n=1;
	//Test f;
	auto v=[&](){
				n=n+5;
				Test t;
				Test f=t;
				std::cout << "Blabla~~" << std::endl;
				return t;
			 };	
	Test x=v();
	// Test v([](Test t){
	// 			return t;
	// 		 }
	// 		);

			// std::move(
			// 			auto x=[]{
			// 					Test t;
			// 					return t;
			// 				 }
			// 	 	)
			// );
	// std::cout << v[0] << " " << v[1] << std::endl;
	 std::cout << n << " " << std::endl;
	 //std::cout << v() << " " << std::endl;

	return 0;

}