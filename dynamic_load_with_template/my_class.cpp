#include "my_class.h"
#include <iostream>

extern "C" MyClass* load() {

		Blast<float>::a = 123;
		Blast<char>::b = 12.3;

		std::cerr << "B<float>::a = " << Blast<float>::a << std::endl;
		std::cerr << "Blast<char>::b = " << Blast<char>::b << std::endl;


    MyClass * thing = new MyClass();
    return thing;
}

extern "C" void unload(MyClass * thing) {

		std::cerr << "B<float>::a = " << Blast<float>::a << std::endl;
		std::cerr << "Blast<char>::b = " << Blast<char>::b << std::endl;
    delete thing;
}