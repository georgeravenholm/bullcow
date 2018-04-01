#include <iostream>
#include <random>
#include <string>

#define MAXGUESSES 10

bool validatestring(std::string& str)
{
	if ( str.length() != 4 ) return false;

	return std::string::npos == str.find_first_not_of("0123456789");
}

int main()
{
	std::cout << "Bulls and Cows" << std::endl;

	// Generate number
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> codegen(0,9);

	int code[4] = { codegen(mt) , codegen(mt) , codegen(mt) , codegen(mt) };

	/*std::cout << "code=" << 
	code[0] << 
	code[1] << 
	code[2] << 
	code[3] << 
	"\n";*/

	std::string guess;
	for (int i=1;i<=MAXGUESSES;++i)
	{
		retry:
		std::cout << "guess (" << i << '/' << MAXGUESSES << ")\t: ";
		std::cin >> guess;

		// validate
		if ( !validatestring(guess) ) goto retry; // try again
	}

	return 0;
}