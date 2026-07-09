#include "RPN.hpp"
#include <vector>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		try
		{
			RPN rpn;
			rpn.doCalc(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	else
	{
		std::cerr << "Error only one arg" << std::endl;
		return 1;
	}
	return 0;
}
