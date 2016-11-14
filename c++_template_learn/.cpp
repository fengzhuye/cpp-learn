#include <iostream>
#include "TemplateDemo.h"

template<class T> A<T>::A(){}

template<class T> T A<T>::g(T a,T b)
{
    return a+b;
}