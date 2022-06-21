#ifndef TEST_HPP
#define TEST_HPP

#include "vector.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"

#include <limits>
#include <random>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

#define RESET   	"\033[0m"
#define BLUE    	"\033[34m"
#define RED			"\033[31m"
#define BOLDCYAN    "\033[1m\033[36m"
#define GREEN 		"\e[92m"
#define BOLD  		"\e[1m"
#define GOOD  		"\033[32mOKAY\033[0m  "
#define FAIL  		"\033[31mFAIL\033[0m  "
#define LEAKS() system("leaks -q a.out | grep \"leaked\"");
#define LOG(x) std::cout << x;
#define STOP std::cin.get();

std::chrono::steady_clock::time_point X;
std::chrono::steady_clock::time_point Y;
long long real;
long long fake;
#define NOW(Z) Z = std::chrono::high_resolution_clock::now();
#define TIMER std::cout << BOLDCYAN << std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count() << " ms  " << RESET;

long long timer( void )
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count());
}

int	check_timer( void )
{
	LOG("TIMEOUT : ");
	if (real != 0 && fake != 0)
	{
		if (fake > real * 20)
		{
			LOG(FAIL); STOP;
			return 1;
		}
		else
		{
			LOG(GOOD);
			return 0;
		}
	}
	LOG(GOOD);
	return 0;
}

template < class T >
int	check_size( ft::vector<T> &x, std::vector<T> &y )
{
	if (x.size() != y.size())
	{
		LOG("SIZE: ");
		LOG(FAIL); STOP;
		return 1;
	}
	LOG("SIZE: ");
	LOG(GOOD);
	return 0;
}

template < class T >
int	check_capacity( ft::vector<T> &x, std::vector<T> &y )
{
	if (x.capacity() != y.capacity())
	{
		LOG("CAPACITY: ");
		LOG(FAIL); STOP;
		return 1;
	}
	LOG("CAPACITY: ");
	LOG(GOOD);
	return 0;
}

template < class T >
int	check_content( ft::vector<T> &x, std::vector<T> &y )
{
	if (x.size() != y.size())
	{
		LOG("CONTENT: ");
		LOG(FAIL); STOP;
		return 1;
	}
	if (x.size() == y.size())
	{
		for (size_t i = 0; i < x.size() && i < y.size(); i++)
		{
			if (x[i] != y[i])
			{
				LOG("CONTENT: ");
				LOG(FAIL); STOP;
				return 1;
			}
		}
	}
	LOG("CONTENT: ");
	LOG(GOOD);
	LOG("\n");
	return 0;
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

template < class T >
void	randomize( ft::vector<T> &x, std::vector<T> &y )
{
	srand(time(0));
	std::generate(y.begin(), y.end(), rand);
	x.resize(y.size());
	for (size_t i = 0; i < x.size(); i++)
	{
		x[i] = y[i];
	}
}

template <class T>
void	test_vector_capacity_fts( ft::vector<T> &ftv, std::vector<T> &stv, size_t r, size_t s, size_t i )
{
	size_t rl = 0;
	size_t fk = 0;	

	std::cout << BLUE << "\n-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "            TEST No " << i << " <> " << r << " elements" << RESET << std::endl;
	std::cout << BLUE << "-----------------------------------------------------------------\n" << RESET << std::endl;
	std::cout << BLUE << "size()" << RESET << std::endl;
	NOW(X); rl = stv.size(); NOW(Y); std::cout << "STD size() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv.size(); NOW(Y); std::cout << "FT size() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "max_size()" << RESET << std::endl;
	NOW(X); rl = stv.max_size(); NOW(Y); std::cout << "STD max_size() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv.max_size(); NOW(Y); std::cout << "FT max_size() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "resize()" << RESET << std::endl;
	NOW(X); stv.resize(r); NOW(Y); std::cout << "STD resize() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(r); NOW(Y); std::cout << "FT resize() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "capacity()" << RESET << std::endl;
	NOW(X); rl = stv.capacity(); NOW(Y); std::cout << "STD capacity() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv.capacity(); NOW(Y); std::cout << "FT capacity() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "empty()" << RESET << std::endl;
	NOW(X); rl = stv.empty(); NOW(Y); std::cout << "STD empty() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv.empty(); NOW(Y); std::cout << "FT empty() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "reserve()" << RESET << std::endl;
	NOW(X); stv.reserve(s); NOW(Y); std::cout << "STD reserve() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.reserve(s); NOW(Y); std::cout << "FT reserve() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	return ;
}

void	test_vector_constructors( void )
{
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "1/ EMPTY VECTOR OF INTS" << RESET << std::endl;
	NOW(X); std::vector<const int> first; NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<const int> _first; NOW(Y); std::cout << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_first == first)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "2/ 1 MILLION INTS WITH VALUE 100" << RESET << std::endl;
	NOW(X); std::vector<int> second(1000000, 100); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<int> _second(1000000, 100); NOW(Y); std::cout << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_second == second)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "3/ ITERATING THROUGH SECOND" << RESET << std::endl;
	NOW(X); std::vector<int> third (second.begin(),second.end()); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<int> _third (_second.begin(),_second.end()); NOW(Y); std::cout << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_third == third)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "4/ COPY OF THE PREVIOUS VECTOR" << RESET << std::endl;
	NOW(X); std::vector<int> fourth(second); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<int> _fourth(_second); NOW(Y); std::cout << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_fourth == fourth)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "5/ BUILT FROM AN ARRAY OF INTS" << RESET << std::endl;
	float t[] = {1.6, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9};
	NOW(X); std::vector<float> fifth(t, t + sizeof(t) / sizeof(float) ); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	float _t[] = {1.6, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9, 2.8, 7.7, 2.9};
	NOW(X); ft::vector<float> _fifth(_t, _t + sizeof(_t) / sizeof(float) ); NOW(Y); std::cout << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_fifth == fifth)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "6/ COPY WITH '=' OPERATOR" << RESET << std::endl;
	NOW(X); std::vector<int> sixth = second; NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<int> _sixth = _second; NOW(Y); std::cout << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_sixth == sixth)
		;
	return ;
}

template <class T>
void	test_vector_access_fts( ft::vector<T> &ftv, std::vector<T> &stv, size_t i )
{
	T rl;
	T fk;	

	std::cout << BLUE << "\n-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "                            TEST No " << i << RESET << std::endl;
	std::cout << BLUE << "-----------------------------------------------------------------\n" << RESET << std::endl;
	std::cout << BLUE << "operator []" << RESET << std::endl;
	NOW(X); rl = stv[0]; NOW(Y); std::cout << "STD operator [] TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv[0]; NOW(Y); std::cout << "FT operator [] TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	if (rl != fk)
	{
		LOG(FAIL); STOP;
		LOG("\n");
	}
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "at()" << RESET << std::endl;
	NOW(X); rl = stv.at(0); NOW(Y); std::cout << "STD at() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv.at(0); NOW(Y); std::cout << "FT at() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	if (rl != fk)
	{
		LOG(FAIL); STOP;
		LOG("\n");
	}
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "front()" << RESET << std::endl;
	NOW(X); stv.front(); NOW(Y); std::cout << "STD front() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.front(); NOW(Y); std::cout << "FT front() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	if (rl != fk)
	{
		LOG(FAIL); STOP;
		LOG("\n");
	}
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "back()" << RESET << std::endl;
	NOW(X); rl = stv.back(); NOW(Y); std::cout << "STD back() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); fk = ftv.back(); NOW(Y); std::cout << "FT back() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	if (rl != fk)
	{
		LOG(FAIL); STOP;
		LOG("\n");
	}
	return ;
}

template <class T>
void	test_vector_modifiers_fts( ft::vector<T> &ftv, std::vector<T> &stv, size_t i )
{
	std::vector<T> to_assign(7, 100);
	ft::vector<T> _to_assign(7, 100);
	std::cout << BLUE << "\n-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "            TEST No " << i << RESET << std::endl;
	std::cout << BLUE << "-----------------------------------------------------------------\n" << RESET << std::endl;
	std::cout << BLUE << "assign(range)" << RESET << std::endl;
	NOW(X); stv.assign(to_assign.begin() + 1, to_assign.end() - 1); NOW(Y); std::cout << "STD assign(range) TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.assign(_to_assign.begin() + 1, _to_assign.end() - 1); NOW(Y); std::cout << "FT assign(range) TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------\n" << RESET << std::endl;
	std::cout << BLUE << "assign(fill)" << RESET << std::endl;
	NOW(X); stv.assign(9, stv.size() - 1); NOW(Y); std::cout << "STD assign(fill) TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.assign(9, ftv.size() - 1); NOW(Y); std::cout << "FT assign(fill) TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "push_back()" << RESET << std::endl;
	NOW(X); stv.push_back(9); NOW(Y); std::cout << "STD push_back() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.push_back(9); NOW(Y); std::cout << "FT push_back() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "pop_back()" << RESET << std::endl;
	NOW(X); stv.pop_back(); NOW(Y); std::cout << "STD pop_back() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.pop_back(); NOW(Y); std::cout << "FT pop_back() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "insert(one)" << RESET << std::endl;
	typename std::vector<T>::iterator it = stv.begin();
	typename ft::vector<T>::iterator _it = ftv.begin();
	NOW(X); stv.insert(it, 9); NOW(Y); std::cout << "STD insert() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.insert(_it, 9); NOW(Y); std::cout << "FT insert() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "insert(fill)" << RESET << std::endl;
	NOW(X); stv.insert(stv.begin(), 9, 9); NOW(Y); std::cout << "STD insert() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.insert(ftv.begin(), 9, 9); NOW(Y); std::cout << "FT insert() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	LOG("\n{stv = ");
	LOG(stv.capacity());
	LOG(" | ftv = ");
	LOG(ftv.capacity());
	LOG("}\n");
	it = stv.begin();
	_it = ftv.begin();
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "insert(range)" << RESET << std::endl;
	NOW(X); stv.insert(it + 1, to_assign.begin(), to_assign.end()); NOW(Y); std::cout << "STD insert() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.insert(_it + 1, _to_assign.begin(), _to_assign.end()); NOW(Y); std::cout << "FT insert() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "erase(one)" << RESET << std::endl;
	NOW(X); stv.erase(stv.begin() + 2); NOW(Y); std::cout << "STD erase() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.erase(ftv.begin() + 2); NOW(Y); std::cout << "FT erase() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "erase(range)" << RESET << std::endl;
	NOW(X); stv.erase(stv.begin(), stv.begin() + 3); NOW(Y); std::cout << "STD erase() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.erase(ftv.begin(), ftv.begin() + 3); NOW(Y); std::cout << "FT erase() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "swap(other)" << RESET << std::endl;
	NOW(X); stv.swap(to_assign); NOW(Y); std::cout << "STD swap() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.swap(_to_assign); NOW(Y); std::cout << "FT swap() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	stv.swap(to_assign);
	ftv.swap(_to_assign);
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "clear()" << RESET << std::endl;
	NOW(X); stv.clear(); NOW(Y); std::cout << "STD clear() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.clear(); NOW(Y); std::cout << "FT clear() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	return ;
}

#endif // !TEST_HPP
