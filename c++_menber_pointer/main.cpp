#include <iostream>

class Foo;

int Foo::* pi;                  // C = Foo, T = int
void (Foo::* pf)(bool, int);    // C = Foo, T = void(bool, int)

class Foo 
{
public:
	int a;
	int b;
	void f(bool b, int i)
	{
		std::cout << i << "bool: " << b << std::endl;
	}
	int Foo::* func(void)
	{
		return &Foo::a;
	}
};

int Foo::* funcPtr(Foo foo, int j)
{
	return &Foo::a;
}



int main()
{
	pi = &Foo::a;
	pf = &Foo::f;
	Foo x;
	x.a = 1;
	x.b = 2;

	int n = x.*pi;     // gets x.a
	(x.*pf)(false, n);  // calls x.f(true, n)

	// pf = &Foo::g;
	(x.*pf)(true, n);  // calls x.g(true, n)
}
