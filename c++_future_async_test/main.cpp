#include <iostream>
#include <string>
#include <future>         // std::promise, std::future, std::async

using namespace std;
int main()
{
	std::future<std::string> f1 = std::async(std::launch::async, [](){ 
		    return std::string("hello, world");  
		}); 

	cout<<f1.get()<<endl; //output: hello, world

	std::future<int> f2 = std::async(std::launch::async, [](){ 
		    cout<<8<<endl;
			return 8;
		}); 

	f2.wait(); //output: 8

	std::future<int> future = std::async(std::launch::async, [](){ 
		    std::this_thread::sleep_for(std::chrono::seconds(3));
		    return 8;  
		}); 
 
    std::cout << "waiting...\n";
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        } else if (status == std::future_status::timeout) {
            std::cout << "timeout\n";
        } else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
        }
    } while (status != std::future_status::ready); 
 
    std::cout << "result is " << future.get() << '\n';
}
