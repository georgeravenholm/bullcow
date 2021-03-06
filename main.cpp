#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <stdlib.h>

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
	std::mt19937 mt;
	mt.seed(static_cast<uint64_t>(std::time(nullptr))); // using time because MiniGW is autistic and doesnt like random numbers!
	std::uniform_int_distribution<int> codegen(0,9);

	int code[4] = { codegen(mt) , codegen(mt) , codegen(mt) , codegen(mt) };
	//int code[4] = {1,4,3,1};
	/*std::cout << "code=" << 
	code[0] << 
	code[1] << 
	code[2] << 
	code[3] << 
	"\n";*/

	std::string guess;
	int bulls,cows,toi=0;
	char buffer[1]; // so convert to const char*

	for (int i=1;i<=MAXGUESSES;++i)
	{
		retry:
		std::cout << "guess (" << i << '/' << MAXGUESSES << ")\t: ";
		std::cin >> guess;

		// validate
		if ( !validatestring(guess) ) goto retry; // try again, using goto because we dont wanna frick up the count!
		// assume from this point onward valid string

		
		bulls = 0;
		cows = 0; // reset

		// counting table
		int counting[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (int k=0;k<4;++k)
			counting[code[k]]++; // count how many of each digit in the code for cow-culation

		// Calculate bulls and cows
		for (int k=0;k<4;++k)
		{
			buffer[0]=guess[k]; 
			toi = atoi(buffer); // toi = currect number of code (char -> int)

			// Bull, matching
			if ( toi==code[k] ) 
			{
				bulls++;
				//counting[toi]--; // avoid cows including bulls
				//continue;
			}
			// Potential cow, if there are any of that digit left
			if ( counting[toi] > 0 )
			{
				counting[toi]--;
				cows++;
			}
			
		}
		cows -= bulls;
		// check for victory
		if (bulls == 4)
		{
			std::cout << "you win! " << i << "/" << MAXGUESSES << " guesses used." << std::endl;
			return 1; // end program
		}

		// print how close
		std::cout << "bulls: " 	<< bulls << std::endl;
		std::cout << "cows: " 	<< cows << std::endl;
	}

	// lost
	std::cout << "sorry, you lost! the code was: " << code[0] << 
	code[1] << 
	code[2] << 
	code[3] << 
	"\n";

	return 0;
}