#include<stdio.h>

template<class T>
struct Blast
{
	static int a ;
	static double b;
	static int getAAA()
	{
		return a;
	}
};
template<class T>
int Blast<T>::a = 11;

template<class T>
double Blast<T>::b = 1.234;



struct MyClass 
{
public:
	static int a;
	int getInt()
	{
		return Blast<int>::a;
	}
	double getDouble()
	{
		return Blast<int>::b;
	}

	bool inc(int i)
	{
		Blast<int>::a = Blast<int>::a + i;
		return true;
	}

	bool inc(double i)
	{
		Blast<int>::b = Blast<int>::b + i;
		return true;
	}


};


//template<class T>
int MyClass::a = 1; 
