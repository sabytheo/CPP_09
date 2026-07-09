#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>

class RPN
{
private:
	std::stack<int> _containers ;
	void doOper(char op);

public:
	RPN();
	RPN(const RPN &src);
	void doCalc(const std::string& str);
	RPN &operator=(const RPN &other);
	~RPN();

};

#endif
