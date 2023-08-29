#include <iostream>

int main() {
	std::cout << "Hello World!" << std::endl;
	std::cout << "What's your name?" << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << "Hello " << name << "!" << std::endl;

	return 0;
}
