/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:57:55 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/30 16:38:39 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP
#include <stack>
#include <iostream>
#include <vector>

template < typename T >
class	MutantStack: public std::stack<T>
{
	public:
		typedef T *iterator;
		iterator	begin()
		{
			std::vector<T> 	v;
			int				n = -1;
			while (!this->empty())
			{
				v.push_back(this->top());
				this->pop();
				++n;
			}
			this->push(v[n]);
			iterator ret = &this->top();
			//std::cout << "--{" << *ret << "}--" << std::endl;
			//std::cout << "-{" << v[0] << "}-" << std::endl;
			//std::cout << "<{" << this->top() << "}>" << std::endl;
			while (n)
			{
				this->push(v[--n]);
				//std::cout << "{" << this->top() << "}" << std::endl;
			}
			//std::cout << "<" << *ret << ">" << std::endl;
			return ret;
		};
		iterator	end()
		{
			//std::cout << "[" << this->top() << "]" << std::endl;
			return &this->top() + 1;
		};
};

#endif
