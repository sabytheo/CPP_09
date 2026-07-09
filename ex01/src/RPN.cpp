#ifndef RPN_CPP
#define RPN_CPP

#include "RPN.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>


RPN::RPN()
{
}

RPN::RPN(const RPN& sources)
{
	*this = sources;
}


RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_containers = other._containers;
	}
	return *this;
}

void RPN::doOper(char oper)
{
	if (this->_containers.size() < 2)
		throw std::runtime_error("Too few numbers");
	int val2 = this->_containers.top();
	this->_containers.pop();
	int val1 = this->_containers.top();
	this->_containers.pop();
	int res = 0;
	switch (oper)
	{
		case '+':
			res = val1 + val2;
			break;
		case '-':
			res = val1 - val2;
			break;
		case '*':
			res = val1 * val2;
			break;
		case '/':
			if ( val2 == 0)
				throw std::runtime_error("can't divide by 0");
			res = val1 / val2;
			break;
		default:
			throw std::runtime_error("CACA");
	}
	this->_containers.push(res);
}

void RPN::doCalc(const std::string& str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];
		if (c == ' ')
			continue;
		else if ((c >= '0' && c <= '9'))
			this->_containers.push(c - '0');
		else if ( c == '+' || c == '-' || c == '*' || c == '/')
			this->doOper(c);
		else
			throw std::runtime_error("BAD CHAR");
	}
	if (this->_containers.size() != 1)
		throw std::runtime_error("Only number between 0 and 9 are valid on args");
	std::cout << this->_containers.top() << std::endl ;
}

RPN::~RPN()
{
}

#endif
