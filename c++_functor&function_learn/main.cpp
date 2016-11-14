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
        return a+b+b_;
    }
    Functor(Functor&&)
    {
	std::cerr << "move" << std::endl;
    }
    Functor(const Functor&)
    {
	std::cerr << "cp" << std::endl;
    }
//    Functor(const Functor&)
//    {
//	std::cerr << "copy" << std::endl;
//    }
    int b_;
private:
	//Functor(const Functor&);
	int a_;
	//Functor(Functor&&);
	//Functor& operator =(const Functor&);
	//Functor& operator =(Functor&&);
};


int main()
{
	Functor f;
	f.b_ = 1;
	std::cerr << f(1,2);
	f.b_ = 2;
	std::function<int(int, int)> b = std::ref(f);
	std::cerr << b(1,2) << std::endl;
//	std::cout << b(2,3) << std::endl;
       std::function<int(int, int)> c = std::bind(&Functor::operator(), std::make_shared<Functor>(), std::placeholders::_1, std::placeholders::_2);
}
