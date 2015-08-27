#ifndef TEMPLATE_DEMO_HXX
#define TEMPLATE_DEMO_HXX

template<class T> class A
{
    public:
        T gggggg(T a,T b);
        A();
};

#include <iostream>
template<class T> A<T>::A(){}

template<class T> T A<T>::gggggg(T a,T b)
{
    return a+b;
}
int i=3;

#endif