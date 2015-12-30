#include <iostream>

class Foo 
{
protected:
	void f()
	{
		std::cout << "bool:" << std::endl;
	}
};

class DeFoo: private Foo
{
public:
	using Foo::f;
	void g()
	{
		f();
	}
private:
	~DeFoo();
};



int main()
{
  DeFoo *d = new DeFoo;
  d->f();
  d->g();
}
