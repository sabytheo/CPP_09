#ifndef BITCOINEXCHANGE_CPP
#define BITCOINEXCHANGE_CPP

#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdlib>

bool isYearBissextile(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	else
		return false;
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _data(src._data)
{
}

void BitcoinExchange::trim(std::string &str) const
{
	size_t first = str.find_first_not_of(" \t\r\n");
	if (first == std::string::npos)
	{
		str = "";
		return;
	}
	size_t last = str.find_last_not_of(" \t\r\n");
	str = str.substr(first, (last - first + 1));
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);

	int Y = std::atoi(year.c_str());
	if (Y < 2008 || Y > 2026)
	{
		std::cout << "Error : year must be between 2008 and 2026" << std::endl;
		return false;
	}
	int M = std::atoi(month.c_str());
	if (M < 1 || M > 12)
	{
		std::cout << "Error : month must be between 1 and 12" << std::endl;
		return false;
	}
	int D = std::atoi(day.c_str());
	int nbDayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isYearBissextile(Y) == true)
		nbDayInMonth[1] = 29;
	if (D < 1 || D > nbDayInMonth[M - 1])
	{
		std::cout << "Error : day must be between 1 and 28,29,30,31 depending on which month you want, and if years is bissextile or not" << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, double &value) const
{
	char *endptr;

	value = strtod(valueStr.c_str(), &endptr);
	if (*endptr != '\0')
	{
		std::cout << "Error : Bad input" << std::endl;
		return false;
	}
	if (value < 0)
	{
		std::cout << "Error : Not a positive number [" << value << "]" << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cout << "Error : Too large Number. Must be between 0 and 1000 [" << value << "]" << std::endl;
		return false;
	}
	return true;
}

int BitcoinExchange::parseCsvData(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		return (1);
	std::string buffer;
	std::getline(file, buffer);

	while (std::getline(file, buffer))
	{
		size_t pos_comma = buffer.find(',');
		if (pos_comma != std::string::npos)
		{
			std::string date = buffer.substr(0, pos_comma);
			std::string rate = buffer.substr(pos_comma + 1);
			_data[date] = std::strtod(rate.c_str(), NULL);
		}
	}
	file.close();
	return 0;
}

int BitcoinExchange::parseInputData(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		return 1;
	std::string buffer;
	std::getline(file, buffer);
	if (buffer != "date | value")
		return (-1);
	while (std::getline(file, buffer))
	{
		size_t pos_pipe = buffer.find('|');
		if (pos_pipe != std::string::npos)
		{
			std::string date = buffer.substr(0, pos_pipe);
			std::string valueStr = buffer.substr(pos_pipe + 1);
			trim(date);
			trim(valueStr);
			if (valueStr.empty())
			{
				std::cout << "Error :  no value for this date. [" << date << "]" << std::endl;
				continue;
			}

			if (!isValidDate(date))
			{
				std::cout << "Error :  not a valid date. [" << date << "]" << std::endl;
				continue;
			}

			double value;
			if (!isValidValue(valueStr, value))
				continue;

			std::map<std::string, double>::iterator it = this->_data.lower_bound(date);
			if (it == this->_data.end() || it->first != date)
			{
				if (it == _data.begin())
				{
					std::cout << "Error : no rate available for [" << date << "]" << std::endl;
					continue;
				}
				--it;
			}
			std::cout << "[" << date << "]" << " | the amount of your btc : [" << value << "]" << " is equal to [" << (value * it->second) << "]" << std::endl;
		}
		else
		{
			std::cout << "Error : Bad Fornat Input [" << buffer << "]" << std::endl;
			continue;
		}
	}
	// file.close();
	return 0;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_data = other._data;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

#endif
