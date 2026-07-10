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

	const std::vector<int> &sortedVec = sorter.getVector();
	std::cout << "After :  ";
	for (size_t i = 0; i < sortedVec.size(); ++i)
	{
		std::cout << sortedVec[i] << " ";
	}
	std::cout << std::endl;

	const std::deque<int> &sortedDeq = sorter.getDeque();
	// std::cout << "After Deq:  ";
	// for (size_t i = 0; i < sortedDeq.size(); ++i)
	// {
	// 	std::cout << sortedDeq[i] << " ";
	// }
	// std::cout << std::endl;

	std::cout << "Time to process a range of " << sortedVec.size()
			  << " elements with std::vector : " << sorter.getTimeVector() << " us" << std::endl;

	std::cout << "Time to process a range of " << sortedDeq.size()
			  << " elements with std::deque  : " << sorter.getTimeDeque() << " us" << std::endl;

	return 0;
}
