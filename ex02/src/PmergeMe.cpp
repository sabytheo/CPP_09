#include "PmergeMe.hpp"
#include <limits>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
	}
	return (*this);
}

bool compareElements(const Element &a, const Element &b)
{
	return a.value < b.value;
}

int PmergeMe::parseArg(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg.empty())
			return (1);
		for (size_t j = 0; j < arg.length(); ++j)
		{
			if (!isdigit(arg[j]))
				return (1);
		}
		long val = std::atol(arg.c_str());
		if ((val < 0) || (val > 2147483647))
			return (1);
		this->_vector.push_back(static_cast<int>(val));
		this->_deque.push_back(static_cast<int>(val));
	}
	return (0);
}

std::vector<int> PmergeMe::Jacob(int size)
{
	std::vector<int> sequence;
	if (size == 0)
		return (sequence);
	int prev = 1;
	int current = 3;

	sequence.push_back(1);
	if (size > 1)
		sequence.push_back(3);
	while (current < size)
	{
		int next = current + 2 * prev;
		sequence.push_back(next);
		prev = current;
		current = next;
	}
	return (sequence);
}
template <typename container>
container MirrorIndexFirstCmp(container &main, container &second, std::vector<std::pair<int, int> > &idPairs)
{
	container orderedSecond;
	for (size_t i = 0; i < main.size(); ++i)
	{
		int idA = main[i].id;
		int idB = -1;

		for (size_t j = 0; j < idPairs.size(); ++j)
		{
			if (idPairs[j].first == idA)
			{
				idB = idPairs[j].second;
				break;
			}
		}

		for (size_t j = 0; j < second.size(); ++j)
		{
			if (second[j].id == idB)
			{
				orderedSecond.push_back(second[j]);
				break;
			}
		}
	}
	return (orderedSecond);
}
template <typename container>
std::vector<int> JacobInsertListIndex(std::vector<int> &jseq, container orderedSecond)
{
	std::vector<int> insertOrderIndex;

	size_t last_insert_index = 1;
	for (size_t i = 1; i < jseq.size(); ++i)
	{
		size_t currentIndex = jseq[i];
		size_t startIndex = std::min(currentIndex, orderedSecond.size());
		for (size_t j = startIndex; j > last_insert_index; --j)
			insertOrderIndex.push_back(j - 1);
		last_insert_index = currentIndex;
	}

	for (size_t i = orderedSecond.size(); i > last_insert_index; --i)
	{
		insertOrderIndex.push_back(i - 1);
	}
	return insertOrderIndex;
}

template <typename container>
void BinaryInsert(std::vector<int> &insertOrderIndex, container &main, container &orderedSecond, std::vector<std::pair<int, int> > &idPairs)
{
	for (size_t i = 0; i < insertOrderIndex.size(); ++i)
	{
		Element target = orderedSecond[insertOrderIndex[i]];
		int idA = -1;
		for (size_t j = 0; j < idPairs.size(); ++j)
		{
			if (idPairs[j].second == target.id)
			{
				idA = idPairs[j].first;
				break;
			}
		}
		typename container::iterator limit = main.end();
		for (typename container::iterator it = main.begin(); it != main.end(); ++it)
		{
			if (it->id == idA)
			{
				limit = it;
				break;
			}
		}
		typename container::iterator pos = std::lower_bound(main.begin(), limit, target, compareElements);
		main.insert(pos, target);
	}
}
template <typename container>
void PmergeMe::sortImpl(container& array)
{
	if (array.size() <= 1)
		return;

	container main;
	container second;
	std::vector<std::pair<int, int> > idPairs;

	Element odd;
	bool isOdd = false;

	for (size_t i = 0; i < array.size(); i += 2)
	{
		if (i + 1 < array.size())
		{
			if (array[i].value > array[i + 1].value)
			{
				main.push_back(array[i]);
				second.push_back(array[i + 1]);
				idPairs.push_back(std::make_pair(array[i].id, array[i + 1].id));
			}
			else
			{
				main.push_back(array[i + 1]);
				second.push_back(array[i]);
				idPairs.push_back(std::make_pair(array[i + 1].id, array[i].id));
			}
		}
		else
		{
			odd = array[i];
			isOdd = true;
		}
	}
	sortImpl(main);
	container orderedSecond = MirrorIndexFirstCmp(main, second, idPairs);
	if (!orderedSecond.empty())
		main.insert(main.begin(), orderedSecond[0]);
	std::vector<int> jseq = Jacob(orderedSecond.size());
	std::vector<int> insertOrderIndex = JacobInsertListIndex(jseq, orderedSecond);
	BinaryInsert(insertOrderIndex, main, orderedSecond, idPairs);
	if (isOdd)
	{
		typename container::iterator pos = std::lower_bound(main.begin(), main.end(), odd, compareElements);
		main.insert(pos, odd);
	}
	array = main;
}

void PmergeMe::exec()
{
	std::vector<Element> vecElements;
	for (size_t i = 0; i < this->_vector.size(); ++i)
	{
		Element e;
		e.value = this->_vector[i];
		e.id = i;
		vecElements.push_back(e);
	}
	struct timeval start, end;
	gettimeofday(&start, NULL);
	sortImpl(vecElements);
	gettimeofday(&end, NULL);
	this->_vectorTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	for (size_t i = 0; i < vecElements.size(); ++i)
		this->_vector[i] = vecElements[i].value;

	// std::cout << "Time to process a range of " << this->_vector.size() << " elements with std::vector : " << timeVec << " us" << std::endl;


	std::deque<Element> deqElements;
	for (size_t i = 0; i < this->_deque.size(); ++i)
	{
		Element e;
		e.value = this->_deque[i];
		e.id = i;
		deqElements.push_back(e);
	}
	gettimeofday(&start, NULL);
	sortImpl(deqElements);
	gettimeofday(&end, NULL);
	this->_dequeTime = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	for (size_t i = 0; i < deqElements.size(); ++i)
		this->_deque[i] = deqElements[i].value;

	// std::cout << "Time to process a range of " << this->_deque.size() << " elements with std::deque : " << timeVec << " us" << std::endl;
}

double PmergeMe::getTimeVector() const
{
	return (this->_vectorTime);
}

double PmergeMe::getTimeDeque() const
{
	return (this->_dequeTime);
}

const std::vector<int> &PmergeMe::getVector() const
{
	return (this->_vector);
}

const std::deque<int> &PmergeMe::getDeque() const
{
	return (this->_deque);
}

PmergeMe::~PmergeMe() {}
