/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:50 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/20 17:04:14 by ablondel         ###   ########.fr       */
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
#include "test.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"

#include <memory>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
		std::cout << "foo is greater than or equal to bar\n";

	LOG("\n");
	ft::vector<int> _foo (3,100);   // three ints with a value of 100
	ft::vector<int> _bar (2,200);   // two ints with a value of 200

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
		std::cout << "foo is greater than or equal to bar\n";
}

void	resize_test()
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

	for (std::vector<int>::iterator stvit = stv.begin(); stvit != stv.end(); stvit++)
	{
		LOG(*stvit);
		LOG("|");
	}
	LOG("\n");
	STOP;
	for (ft::vector<int> ::iterator ftvit = ftv.begin(); ftvit != ftv.end(); ftvit++)
	{
		LOG(*ftvit);
		LOG("|");
	}
	LOG("\n");
	STOP;
	for (std::vector<int>::reverse_iterator rstvit = stv.rbegin(); rstvit != stv.rend(); rstvit++)
	{
		LOG(*rstvit);
		LOG("|");
	}
	LOG("\n");
	STOP;
	for (ft::vector<int> ::reverse_iterator rftvit = ftv.rbegin(); rftvit != ftv.rend(); rftvit++)
	{
		LOG(*rftvit);
		LOG("|");
	}
	LOG("\n");
	STOP;
}

int		main( void )
{
	//test_vector_constructors();
	//run_cap_test();
	//run_access_test();
	//run_modifiers_test();
	//run_operator_test();
	resize_test();
	LOG("*****************************************************************\n");
	LEAKS();
	LOG("*****************************************************************\n");
	return 0;
}
