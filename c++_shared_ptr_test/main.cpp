#include <iostream>
#include <memory>

class A
{
	public:
		int num_a_;
	A():num_a_(7)
	{
		std::cout << "A" << std::endl;
	}
	~A()
	{
		std::cout << "~A" << std::endl;
	}
};
class B : public A
{
	public:
		int num_b_;
	B():num_b_(8)
	{
		std::cout << "B" << std::endl;
	}
	~B()
	{
		std::cout << "~B" << std::endl;
	}
};

void func(std::shared_ptr<A> a)
{
	std::cout << a->num_a_ << std::endl;
	std::shared_ptr<B> b = std::static_pointer_cast<B>( a);
std::cout << b->num_b_ << std::endl;
}

int main()
{
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();
	func(b);
	return 0;

}
