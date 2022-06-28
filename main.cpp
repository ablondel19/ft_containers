/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_main.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:46:26 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/27 10:58:47 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <memory>
#include <iterator>
#include <vector>
#include <list>
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
#define NOW(Z) Z = std::chrono::high_resolution_clock::now();
#define TIMER std::cout << BOLDCYAN << std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count() << " ms  " << RESET;

long long timer( void )
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count());
}

#define TESTED_NAMESPACE ft
#define UNDERLYING_TYPE int
#define T ft::vector

void	check_size( TESTED_NAMESPACE::stack<T <UNDERLYING_TYPE> > _stk )
{
	LOG("SIZE: ");
	LOG(BOLDCYAN);
	LOG(_stk.size());
	LOG("\n");
	LOG(RESET);
}

void	test_stack( TESTED_NAMESPACE::stack<T <UNDERLYING_TYPE> > _stk )
{
	std::cout << BLUE << "\n-----------------------------------------------------------------" << RESET << std::endl;
	NOW(X); /* _stack.FUNC() */ ; NOW(Y); std::cout << "TIME: "; TIMER;	std::cout << std::endl;
	check_size(_stk);
}

int		main( void )
{
	TESTED_NAMESPACE::stack<T <UNDERLYING_TYPE> > stk;
	test_stack(stk);
	LOG("*****************************************************************\n");
	LEAKS();
	LOG("*****************************************************************\n");
	return 0;
}
