#ifndef TEST_HPP
#define TEST_HPP
#include "vector.hpp"
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <memory>
#define RESET   	"\033[0m"
#define BLUE    	"\033[34m"
#define RED			"\033[31m"
#define BOLDCYAN    "\033[1m\033[36m"
#define GREEN 		"\e[92m"
#define BOLD  		"\e[1m"
#define GOOD  		"\e[92m	GOOD\033[0m\n"
#define FAIL  		"\033[31m	FAIL\033[0m\n"
#define STOP() std::cout << BLUE << "---Press any key to jump to the next LOG()..." << RESET << std::endl; std::cin.get();
#define CLEAR() system("clear");
#define LEAKS() system("leaks a.out");
#define LOG(x) std::cout << x;
#define LOGFAIL(info, x, y) std::cout << RED << info << " : " << x  << " -VS- " << y << RESET << " ";
#define LOGGOOD(info, x, y) std::cout << GREEN << info << " : " << x  << " -VS- " << y << RESET << " ";
#define LOGSTOP(info, x) std::cout << BOLDCYAN << info << " : " << x << RESET << std::endl; STOP();

template < class T >
bool operator==(ft::vector<T> &x, std::vector<T> &y)
{
	bool error = 0;

	if (x.size() != y.size())
	{
		LOGFAIL("Size mismatch    ", x.size(), y.size());
		LOG(FAIL);
		error = 1;
	}
	if (x.capacity() != y.capacity())
	{
		LOGFAIL("Capacity mismatch", x.capacity(), y.capacity());
		LOG(FAIL);
		error = 1;
	}
	if (error)
		return 0;
	LOGGOOD("Matching size    ", x.size(), y.size());
	LOG(GOOD);
	LOGGOOD("Matching capacity", x.capacity(), y.capacity());
	LOG(GOOD)
	return 1;
}

#endif // !TEST_HPP
