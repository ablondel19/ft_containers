#ifndef TEST_HPP
#define TEST_HPP
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "vector.hpp"
#include "iterator.hpp"
#include "types.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RESET   	"\033[0m"
#define BLUE    	"\033[34m"
#define RED			"\033[31m"
#define BOLDCYAN    "\033[1m\033[36m"
#define GREEN 		"\e[92m"
#define BOLD  		"\e[1m"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define GOOD  		"\033[32mOKAY\033[0m\n"
#define FAIL  		"\033[31mFAIL\033[0m\n"
#define LEAKS() system("leaks -q a.out | grep \"leaked\"");
#define LOG(x) std::cout << x;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::chrono::steady_clock::time_point X;
std::chrono::steady_clock::time_point Y;
long long real;
long long fake;
#define NOW(Z) Z = std::chrono::high_resolution_clock::now();
#define TIMER std::cout << BOLDCYAN << std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count() << " ms" << RESET;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long timer( void )
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count());
}

void	check_timer( void )
{
	LOG("TIMEOUT : ");
	if (fake > real * 20)
	{
		LOG(FAIL);
	}
	else
	{
		LOG(GOOD);
	}
	return ;
}

template < class T >
int	check_size( ft::vector<T> &x, std::vector<T> &y )
{
	if (x.size() != y.size())
	{
		LOG("SIZE    : ");
		LOG(FAIL);
		return 0;
	}
	LOG("SIZE    : ");
	LOG(GOOD);
	return 1;
}

template < class T >
int	check_capacity( ft::vector<T> &x, std::vector<T> &y )
{
	if (x.capacity() != y.capacity())
	{
		LOG("CAPACITY: ");
		LOG(FAIL);
		return 0;
	}
	LOG("CAPACITY: ");
	LOG(GOOD);
	return 1;
}

template < class T >
int	check_content( ft::vector<T> &x, std::vector<T> &y )
{
	if (x.size() != y.size())
	{
		LOG("CONTENT : ");
		LOG(FAIL);
		return 0;
	}
	if (x.size() == y.size())
	{
		for (size_t i = 0; i < x.size() && i < y.size(); i++)
		{
			if (x[i] != y[i])
			{
				LOG("CONTENT : ");
				LOG(FAIL);
				return 0;
			}
		}
	}
	LOG("CONTENT : ");
	LOG(GOOD);
	return 1;
}

template < class T >
bool operator==( ft::vector<T> &x, std::vector<T> &y )
{
	check_timer();
	check_size(x, y);
	check_capacity(x, y);
	check_content(x, y);
	LOG("\n");
	return 0;
}

#endif // !TEST_HPP
