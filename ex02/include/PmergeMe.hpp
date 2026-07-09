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
		double _vectorTime;
		double _dequeTime;

	public :
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();


		std::vector<int> Jacob(int size);
		template <typename container>
		void sortImpl(container& array);
		int parseArg(int argc, char **argv);
		void exec();

		const std::deque<int>& getDeque() const;
		const std::vector<int>& getVector() const;

		double getTimeVector() const;
		double getTimeDeque() const;
};

#endif
