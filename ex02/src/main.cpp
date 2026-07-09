#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: No sequence provided." << std::endl;
		return 1;
	}

	PmergeMe sorter;

	if (sorter.parseArg(argc, argv) != 0)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::cout << "Before: ";
	for (int i = 1; i < argc; ++i)
	{
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;

	sorter.exec();

	std::cout << "After:  ";
	const std::vector<int> &sortedVec = sorter.getVector();
	for (size_t i = 0; i < sortedVec.size(); ++i)
	{
		std::cout << sortedVec[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
