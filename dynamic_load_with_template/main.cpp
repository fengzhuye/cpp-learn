#include "Plugin.h"
#include "my_class.h"
#include <iostream>



int main()
{

	Blast<float>::a = 555;
	Blast<char>::b = 77.3;

	try
	{
		Plugin<MyClass> * plugin = new Plugin<MyClass>("./libmy_class.so", "load", "unload");
		MyClass * thing = plugin->Load();

		std::cerr << "B<float>::a = " << Blast<float>::a << std::endl;
		std::cerr << "Blast<char>::b = " << Blast<char>::b << std::endl;

		std::cerr << "getInt: " << thing->getInt() << std::endl;
		std::cerr << "getDouble: " << thing->getDouble() << std::endl;

		std::cerr << "incInt: " << thing->inc(3) << std::endl;
		std::cerr << "incDouble: " << thing->inc(1.1) << std::endl;

		std::cerr << "getInt: " << thing->getInt() << std::endl;
		std::cerr << "getDouble: " << thing->getDouble() << std::endl;

		std::cerr << "Blast<int>::a = " << Blast<int>::a << std::endl;
		std::cerr << "Blast<int>::b = " << Blast<int>::b << std::endl;

		plugin->Unload();

	}
	catch(PluginException& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
	/** use thing **/
	

	return 0;
}