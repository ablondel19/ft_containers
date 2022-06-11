/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:50 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/11 22:19:42 by ablondel         ###   ########.fr       */
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
#include <memory>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>

void	test_contructors( void )
{
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third
	int myints[] = {16,2,77,29};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	ft::vector<int> _first;                                 // empty vector of ints
	ft::vector<int> _second (4,100);                        // four ints with value 100
	ft::vector<int> _third (_second.begin(),_second.end()); // iterating through second
	ft::vector<int> _fourth (_third);                       // a copy of third
	int _myints[] = {16,2,77,29};
	ft::vector<int> _fifth(_myints, _myints + sizeof(_myints) / sizeof(int) );
	ft::vector<int> _sixth = _fifth;


	LOG("Empty vector of ints\n");
	if (_first == first)
		;
	LOG("Four ints with value 100\n");
	if (_second == second)
		;
	LOG("Iterating through another vector\n");
	if (_third == third)
		;
	LOG("Copy of another vector\n");
	if (_fourth == fourth)
		;
	LOG("Built from an array of ints\n");
	if (_fifth == fifth)
		;
	LOG("Built with '=' operator\n");
	if (_sixth == fifth)
		;
}

void	test_const( void )
{
	std::vector<const int> first;                                // empty vector of ints
	std::vector<const int> second (4,100);                       // four ints with value 100
	std::vector<const int> third (second.begin(),second.end());  // iterating through second
	std::vector<const int> fourth (third);                       // a copy of third
	int myints[] = {16,2,77,29};
	std::vector<const int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	ft::vector<const int> _first;                                 // empty vector of ints
	ft::vector<const int> _second (4,100);                        // four ints with value 100
	ft::vector<const int> _third (_second.begin(),_second.end()); // iterating through second
	ft::vector<const int> _fourth (_third);                       // a copy of third
	int _myints[] = {16,2,77,29};
	ft::vector<const int> _fifth(_myints, _myints + sizeof(_myints) / sizeof(int) );
	ft::vector<const int> _sixth = _fifth;


	LOG("Empty vector of ints\n");
	if (_first == first)
		;
	LOG("Four ints with value 100\n");
	if (_second == second)
		;
	LOG("Iterating through another vector\n");
	if (_third == third)
		;
	LOG("Copy of another vector\n");
	if (_fourth == fourth)
		;
	LOG("Built from an array of ints\n");
	if (_fifth == fifth)
		;
	LOG("Built with '=' operator\n");
	if (_sixth == fifth)
		;
}

int		main( void )
{
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "EMPTY VECTOR OF INTS" << RESET << std::endl;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	NOW(X); std::vector<int> first; NOW(Y); std::cout << std::left << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<int> _first; NOW(Y); std::cout << std::left << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_first == first)
		;

	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	std::cout << BLUE << "FOUR INTS WITH VALUE FOUR" << RESET << std::endl;
	std::cout << BLUE << "-----------------------------------------------------------------" << RESET << std::endl;
	NOW(X); std::vector<int> second(4, 100); NOW(Y); std::cout << std::left << "STD TIME: "; TIMER;	std::cout << std::endl;
	real = timer();
	NOW(X); ft::vector<int> _second(4, 100); NOW(Y); std::cout << std::left << "FT  TIME: "; TIMER;	std::cout << std::endl;
	fake = timer();
	if (_second == second)
		;

	
	
	



	
	LEAKS();
	return 0;
}
