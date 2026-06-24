#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double> _data;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();


	bool isValidDate(const std::string &date) const;
	bool isValidValue(const std::string &valueStr, double &value) const;
	void trim(std::string &str) const;
	int parseCsvData(const std::string &filename);
	int parseInputData(const std::string &filename);
};

#endif
