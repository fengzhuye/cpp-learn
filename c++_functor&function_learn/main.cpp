#include <iostream>
#include <functional>
#include <memory>

class Functor
{
public:
    Functor()
    {
	std::cerr << "ctor" << std::endl;
    }
    int operator() (int a, int b)
    {
        return a+b;
    }
    Functor(Functor&&)
    {
	std::cerr << "move" << std::endl;
    }
//    Functor(const Functor&)
//    {
//	std::cerr << "copy" << std::endl;
//    }
private:
	Functor(const Functor&);
	//Functor(Functor&&);
	//Functor& operator =(const Functor&);
	//Functor& operator =(Functor&&);
};


int main()
{
	Functor f;
	//std::function<int(int, int)> a = std::ref(f);
//	std::function<int(int, int)> b = Functor();
//	std::cout << b(2,3) << std::endl;
       std::function<int(int, int)> c = std::bind(&Functor::operator(), std::make_shared<Functor>(), std::placeholders::_1, std::placeholders::_2);
}
