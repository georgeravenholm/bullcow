#include <iostream>
#include <random>

int main()
{
	std::cout << "Bulls and Cows" << std::endl;

	// Generate number
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> codegen(0,9);

	int code[4] = { codegen(mt) , codegen(mt) , codegen(mt) , codegen(mt) };

	std::cout << "code=" << 
	code[0] << 
	code[1] << 
	code[2] << 
	code[3] << 
	"\n";

	return 0;
}