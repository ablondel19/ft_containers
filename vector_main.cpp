/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:50 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/26 20:52:10 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	https://cdn.intra.42.fr/pdf/pdf/34895/fr.subject.pdf
**	https://www.cplusplus.com/reference/vector/vector/
**	https://anderberg.me/2016/07/04/c-custom-iterators/
**	https://stackoverflow.com/questions/21275190/c-custom-collection-reverse-iterator-with-similar-behaviour-to-stdvector-imp
**	https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/
**  https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/
**  https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/
**  https://www.fluentcpp.com/2018/04/27/tag-dispatching/
*/

#include "vector.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"

#include <memory>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>

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

void	run_constructors_test( void )
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

void	run_cap_test( void )
{
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<int> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<int> stv(r, s);
		ft::vector<int> ftv(r, s);
		randomize(ftv, stv);
		test_vector_capacity_fts(ftv, stv, r, s, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned int> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned> stv(r, s);
		ft::vector<unsigned> ftv(r, s);
		randomize(ftv, stv);
		test_vector_capacity_fts(ftv, stv, r, s, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned long long> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned long long> stv(r, s);
		ft::vector<unsigned long long> ftv(r, s);
		randomize(ftv, stv);
		test_vector_capacity_fts(ftv, stv, r, s, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned short> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned short> stv(r, s);
		ft::vector<unsigned short> ftv(r, s);
		randomize(ftv, stv);
		test_vector_capacity_fts(ftv, stv, r, s, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<signed char> gen(1, i);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<signed char> stv(r, s);
		ft::vector<signed char> ftv(r, s);
		randomize(ftv, stv);
		test_vector_capacity_fts(ftv, stv, r, s, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<float> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<float> stv(r, s);
		ft::vector<float> ftv(r, s);
		randomize(ftv, stv);
		test_vector_capacity_fts(ftv, stv, r, s, i);
	}
	return ;
}

void	run_access_test( void )
{
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<int> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<int> stv(r, s);
		ft::vector<int> ftv(r, s);
		randomize(ftv, stv);
		test_vector_access_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned int> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned> stv(r, s);
		ft::vector<unsigned> ftv(r, s);
		randomize(ftv, stv);
		test_vector_access_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned long long> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned long long> stv(r, s);
		ft::vector<unsigned long long> ftv(r, s);
		randomize(ftv, stv);
		test_vector_access_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned short> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned short> stv(r, s);
		ft::vector<unsigned short> ftv(r, s);
		randomize(ftv, stv);
		test_vector_access_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<signed char> gen(1, i);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<signed char> stv(r, s);
		ft::vector<signed char> ftv(r, s);
		randomize(ftv, stv);
		test_vector_access_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<float> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<float> stv(r, s);
		ft::vector<float> ftv(r, s);
		randomize(ftv, stv);
		test_vector_access_fts(ftv, stv, i);
	}
	return ;
}

void	run_modifiers_test( void )
{
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<int> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<int> stv(r, s);
		ft::vector<int> ftv(r, s);
		randomize(ftv, stv);
		test_vector_modifiers_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned> stv(r, s);
		ft::vector<unsigned> ftv(r, s);
		randomize(ftv, stv);
		test_vector_modifiers_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned long long> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned long long> stv(r, s);
		ft::vector<unsigned long long> ftv(r, s);
		randomize(ftv, stv);
		test_vector_modifiers_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<unsigned short> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<unsigned short> stv(r, s);
		ft::vector<unsigned short> ftv(r, s);
		randomize(ftv, stv);
		test_vector_modifiers_fts(ftv, stv, i);
	}
	for (size_t i = 1; i <= 10; i++)
	{
		std::mt19937 rng(i);
		std::uniform_int_distribution<float> gen(1, i * 1000000);
		size_t r = gen(rng);
		size_t s = gen(rng);
		std::vector<float> stv(r, s);
		ft::vector<float> ftv(r, s);
		randomize(ftv, stv);
		test_vector_modifiers_fts(ftv, stv, i);
	}
	return ;
}

void	run_operator_test()
{
	LOG("\n\nOPERATORS TESTS\n");
	std::vector<int> foo (3,100);   // three ints with a value of 100
	std::vector<int> bar (2,200);   // two ints with a value of 200

	LOG("Expected output:\n");
	if (foo == bar)
		std::cout << "foo and bar are equal\n";
	if (foo != bar)
		std::cout << "foo and bar are not equal\n";
	if (foo <  bar)
		std::cout << "foo is less than bar\n";
	if (foo >  bar)
		std::cout << "foo is greater than bar\n";
	if (foo <= bar)
		std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar)
		std::cout << "foo is greater than or equal to bar\n" << std::endl;

	ft::vector<int> _foo (3,100);   // three ints with a value of 100
	ft::vector<int> _bar (2,200);   // two ints with a value of 200
	LOG("My output:\n");
	if (_foo == _bar)
		std::cout << "foo and bar are equal\n";
	if (_foo != _bar)
		std::cout << "foo and bar are not equal\n";
	if (_foo <  _bar)
		std::cout << "foo is less than bar\n";
	if (_foo >  _bar)
		std::cout << "foo is greater than bar\n";
	if (_foo <= _bar)
		std::cout << "foo is less than or equal to bar\n";
	if (_foo >= _bar)
		std::cout << "foo is greater than or equal to bar\n" << std::endl;
}

void	run_iterators_test()
{
	std::vector<int> stv;
	ft::vector<int> ftv;
	for (size_t i = 0; i < 10; i++)
	{
		stv.push_back(i);
		ftv.push_back(i);
	}
	
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "resize()" << RESET << std::endl;
	NOW(X); stv.resize(5); NOW(Y); std::cout << "STD resize() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(5); NOW(Y); std::cout << "FT resize() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	
	NOW(X); stv.resize(8, 100); NOW(Y); std::cout << "STD resize() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(8, 100); NOW(Y); std::cout << "FT resize() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;

	NOW(X); stv.resize(12); NOW(Y); std::cout << "STD resize() TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(12); NOW(Y); std::cout << "FT resize() TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	LOG("std iterator:\n")
	for (std::vector<int>::iterator stvit = stv.begin(); stvit != stv.end(); stvit++)
	{
		LOG(*stvit);
		LOG("|");
	}
	LOG("\nft iterator:\n");
	for (ft::vector<int> ::iterator ftvit = ftv.begin(); ftvit != ftv.end(); ftvit++)
	{
		LOG(*ftvit);
		LOG("|");
	}
	LOG("\nstd reverse iterator:\n");
	for (std::vector<int>::reverse_iterator rstvit = stv.rbegin(); rstvit != stv.rend(); rstvit++)
	{
		LOG(*rstvit);
		LOG("|");
	}
	//LOG("\nft reverse iterator:\n");
	//for (ft::vector<int> ::reverse_iterator rftvit = ftv.rbegin(); rftvit != ftv.rend(); rftvit++)
	//{
	//	LOG(*rftvit);
	//	LOG("|");
	//}
	//LOG("\n");
}

void	run_str_test()
{
	std::vector<std::string> stv;
	ft::vector<std::string> ftv;
	for (size_t i = 0; i < 10000; i++)
	{
		stv.push_back("test");
		ftv.push_back("test");
	}
	
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "std::string test" << RESET << std::endl;
	NOW(X); stv.resize(5); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(5); NOW(Y); std::cout << "FT  TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
	
	NOW(X); stv.resize(8000000, "yoyo"); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(8000000, "yoyo"); NOW(Y); std::cout << "FT  TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;

	NOW(X); stv.resize(12); NOW(Y); std::cout << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ftv.resize(12); NOW(Y); std::cout << "FT  TIME : "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (ftv == stv)
		;
}

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int
#include <list>

//template < class T >
int	check_size2( TESTED_NAMESPACE::vector<TESTED_TYPE> &x )
{
	LOG("SIZE: ");
	LOG(x.size());
	LOG("\n");
	return 0;
}


int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit = vct.begin();

	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit(it);

	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit(rit);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_(it);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_2(cit);
	return (0);
}
