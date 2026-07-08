#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <sys/time.h>
#include <algorithm>

struct Element
{
	int value;
	int id;
};

class PmergeMe
{
	private :
		std::vector<int> _vector;
		std::deque<int> _deque;

	public :
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();


		std::vector<int> Jacob(int size);
		void sortVectorImpl(std::vector<Element>& array);
		// void sortDequeImpl(std::vector<Element>& array);

		int parseArg(int argc, char **argv);
		void exec();

		const std::vector<int>& getVector() const;
};

#endif
