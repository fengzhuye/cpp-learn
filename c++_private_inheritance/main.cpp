// #include "car.hpp"
// #include "engine.hpp"

// int main()
// {
//     Car car(2);
//     car.start();
//     return 0;
// }


// #include <iostream>

// class Wilma {
// public:
// 	Wilma()//:nnn(6),nn(7),n(8)
// 	{};
// 	void someFunc()
// 	{
// 		std::cout << "someFunc\n";
// 		fredCallsWilma();
// 	}
// 	int nnn()
// 	{return 3;};
// protected:
//   	void fredCallsWilma()
//     {
//       std::cout << "Wilma::fredCallsWilma()\n";
//       wilmaCallsFred();
//     }
//     int getN()
//     {
//     	return 3;
//     }
//     int nn()
//     {return 2;};
// private:
// 	virtual void wilmaCallsFred()   // A pure virtual function
// 	{
// 		std::cout << "wilma::wilma\n";
// 	}
// 	int n()
// 	{return 1;};
// };

// class Bla {
//   virtual void callBla()   // A pure virtual function
//   {
//   	std::cout << "callBla::callBla\n";
//   }
// };

// class Fred : public Wilma, public Bla {
// public:
// 	Fred()//:n(9)
// 	{};
//   void barney()
//     {
//       std::cout << "Fred::barney()\n";
//       fredCallsWilma();
//     }
//     Fred* getThis()
//     {
//     	return this;
//     }
//     Wilma* useThis()
//     {
//     	Wilma* pbase;
//     	pbase = getThis();
//     	return pbase;
//     }
//     int getBaseN()
//     {
//     	return getN(); 
//     }
//     int getDeN()
//     {
//     	return 1;
//     }
// protected:
//   virtual void wilmaCallsFred()
//     {
//       std::cout << "Fred::wilmaCallsFred()\n";
//     }
// public:
// 	int n()
// 	{return 6;};
// 	int nn()
// 	{return 5;};
// 	// int nnn()
// 	// {return 4;};
// };

// void someFunc(Bla* pbase)
// {
// 	std::cout << "base pointer in funct\n";
// }
// int main()
// {
// 	Fred f;
// 	Wilma* pbase = &f;
// 	// std::cout << pbase->nn() << std::endl;
// 	std::cout << f.nn() << std::endl;
// }



#include <string>  
#include <iostream> 
using namespace std ; 

class Base 
{ 
public:
	Base():num(1)
	{}

    string classID(char c) const
    { 
       return string("Base") ; 
    } 

private: 
    virtual void doWork(char c)
    {
    	cout<<"base dowork"<<endl ; 

    }
public:  
    virtual void work() 
    { 
        cout<<"this class id is "<<classID('a')<<endl ;  
        //doWork(30) ; 
    } 

    virtual ~Base() 
    { 
    }
  	void write(int n)
  	{
  		num = n;
  	}
  	int read()
  	{
  		return num;
  	}
private:
	int num;
}; 

class DerivedA : public Base 
{ 
public: 
	int i;
	DerivedA():i(7)
	{}
    string classID(double i) const  
    { 
       return string("DerivedA") ;
    }
public: 
    string classID(char i) const  
    { 
       return string("over DerivedA") ;
    } 

public: 
	// using Base::doWork;
    void doWork(double i) 
    { 

       cout<<"this is DerivedA doWork !"<<endl ; 
    } 
};

int main()
{
	DerivedA* pb = new DerivedA();
	// cout << pb->i<<endl ; 
	// pb->doWork(1.23);
	cout << pb->read() << endl;
	pb->write(1314);
	cout << pb->read() << endl;
	delete pb;
}