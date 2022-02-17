/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:12:05 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/30 16:05:48 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <list>
/*
int main()
{
	MutantStack<int> mstack;
	mstack.push(1);
	//std::cout << mstack.top() << std::endl;
	mstack.push(2);
	//std::cout << mstack.top() << std::endl;
	mstack.push(3);
	//std::cout << mstack.top() << std::endl;
	mstack.push(4);
	//std::cout << mstack.top() << std::endl;
	mstack.push(5);
	//std::cout << mstack.top() << std::endl;
	mstack.push(6);
	//std::cout << mstack.top() << std::endl;
	//std::cout << mstack.size() << std::endl;
	std::cout << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	//std::cout << "<" << *it << ">" << std::endl;
	//std::cout << "<" << *ite << ">" << std::endl;
	//++it;
	//--it;
	while (it != ite)
	{
		std::cout << "[" << *it << "]";
		++it;
	}
	std::cout << std::endl;
	std::stack<int> s(mstack);
	return 0;
}
*/

int main()
{
	MutantStack<char> mstack;
	mstack.push('a');
	//std::cout << mstack.top() << std::endl;
	mstack.push('b');
	//std::cout << mstack.top() << std::endl;
	mstack.push('c');
	//std::cout << mstack.top() << std::endl;
	mstack.push('d');
	//std::cout << mstack.top() << std::endl;
	mstack.push('e');
	//std::cout << mstack.top() << std::endl;
	mstack.push('f');
	//std::cout << mstack.top() << std::endl;
	//std::cout << mstack.size() << std::endl;
	std::cout << std::endl;
	MutantStack<char>::iterator it = mstack.begin();
	MutantStack<char>::iterator ite = mstack.end();
	//std::cout << "<" << *it << ">" << std::endl;
	//std::cout << "<" << *ite << ">" << std::endl;
	//++it;
	//--it;
	while (it != ite)
	{
		std::cout << "[" << *it << "]";
		++it;
	}
	std::cout << std::endl;
	std::stack<char> s(mstack);
	return 0;
}

/*
int main()
{
	std::list<int> mstack;
	mstack.push_back(1);
	//std::cout << mstack.top() << std::endl;
	mstack.push_back(2);
	//std::cout << mstack.top() << std::endl;
	mstack.push_back(3);
	//std::cout << mstack.top() << std::endl;
	mstack.push_back(4);
	//std::cout << mstack.top() << std::endl;
	mstack.push_back(5);
	//std::cout << mstack.top() << std::endl;
	mstack.push_back(6);
	//std::cout << mstack.top() << std::endl;
	//std::cout << mstack.size() << std::endl;
	std::cout << std::endl;
	std::list<int>::iterator it = mstack.begin();
	std::list<int>::iterator ite = mstack.end();
	//std::cout << "<" << *it << ">" << std::endl;
	//std::cout << "<" << *ite << ">" << std::endl;
	//++it;
	//--it;
	while (it != ite)
	{
		std::cout << "[" << *it << "]";
		++it;
	}
	std::cout << std::endl;
	std::list<int> s(mstack);
	while (!s.empty())
	{
		std::cout << "[" << s.front() << "]";
		s.pop_front();
	}
	return 0;
}
*/