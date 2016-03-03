#include <iostream>
#include <functional>

class Functor
{
public:
	Functor()=default;
    int operator() (int a, int b)
    {
        return a+b;
    }
private:
	Functor(const Functor&);
};


int main()
{
	Functor f;
	std::function<int(int, int)> a = std::ref(f);
	std::cout << a(2,3) << std::endl;
}
