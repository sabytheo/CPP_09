#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		BitcoinExchange bitcoin;

		if (bitcoin.parseCsvData("data.csv") != 0)
		{
			std::cout << "Error : could not open data.csv" << std::endl;
			return 1;
		}
		std::string filename = argv[1];
		if (bitcoin.parseInputData(filename) != 0)
		{
			std::cout << "Error : could not open the file passed in argument" << std::endl;
			return 1;
		}
		return 0;
	}
	else
	{
		std::cout << "Error : must be one argument, the name of the file" << std::endl;
		return 1;
	}
}
