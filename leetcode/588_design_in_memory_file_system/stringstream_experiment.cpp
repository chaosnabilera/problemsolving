#include <iostream>
#include <sstream>
#include <string>

int main(){
	std::stringstream ss;
	ss << "coding";
	std::cout << ss.str() << std::endl;
	ss << " is";
	std::cout << ss.str() << std::endl;
	ss << " kinda";
	std::cout << ss.str() << std::endl;
	ss << " fun";
	std::cout << ss.str() << std::endl;
}