#include <iostream>
#include <cmath>
int main()
{
       const double pi = 3.141592653589793238;  // double 有效位数为 16
       double d1 = 2.1212;
       double d2 = -5.1515;
       double d3 = 9.1919;
       int k1 = d1/(2*pi);
       int k2 = d2/(2*pi);
       int k3 = d3/(2*pi);

       double t1 = std::fmod(d3,pi);
       double t2 = std::remainder(d3, 2*pi);
       
       // 千万别在算法中将系数写成整数
       double t3 = 1/2*d3;  // 根据先后顺序得出 t3=0 !!!
       
       std::cerr << "k_1: " << k1 << std::endl;
       std::cerr << "k_2: " << k2 << std::endl;
       std::cerr << "k_3: " << k3 << std::endl;
       std::cerr << "t_1: " << t1 << std::endl;
       std::cerr << "t_2: " << t2 << std::endl;
       std::cerr << "t_3: " << t3 << std::endl;
}
