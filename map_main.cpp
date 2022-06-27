/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 07:49:08 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/27 10:44:54 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

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
long long ms = 0;
long long fake = 0;
#define NOW(Z) Z = std::chrono::high_resolution_clock::now();
#define TIMER std::cout << BOLDCYAN << std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count() << " ms  " << RESET;

long long timer( void )
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(Y - X).count());
}

#define TESTED_NAMESPACE ft
#define T1 int
#define T2 std::string

void	check_size( TESTED_NAMESPACE::map<T1, T2> _map )
{
	LOG("SIZE: ");
	LOG(BOLDCYAN);
	LOG(_map.size());
	LOG("\n");
	LOG(RESET);
}

void	test_map( TESTED_NAMESPACE::map<T1, T2> _map )
{
	std::cout << BLUE << "\n-----------------------------------------------------------------" << RESET << std::endl;
	NOW(X); /* _map.FUNC() */ ; NOW(Y); std::cout << "TIME: "; TIMER;	std::cout << std::endl;
	ms = timer();
	check_size(_map);
}

int		main( void )
{
	TESTED_NAMESPACE::map<T1, T2> mp;
	test_map(mp);
	LOG("*****************************************************************\n");
	LEAKS();
	LOG("*****************************************************************\n");
	return 0;
}
