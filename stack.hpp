/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:49:00 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/26 17:09:35 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef size_t		size_type;
			typedef	T			value_type;
			typedef Container	container_type;
			container_type		container;
			
			explicit stack (const container_type& ctnr = container_type()) : container(ctnr) {}
			bool empty() const { return container.empty(); }
			size_type size() const { return container.size(); }
			value_type& top() { return container.back(); }
			const value_type& top() const { return container.back(); }
			void push (const value_type& val) { container.push_back(val); };
			void pop() { container.pop_back(); }

	};
	template <class T, class Container>
  	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.container == rhs.container;
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.container != rhs.container;
	}
	
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.container < rhs.container;
	}
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.container <= rhs.container;
	}
	
	template <class T, class Container>	
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.container > rhs.container;
	}
	
	template <class T, class Container>
  	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.container >= rhs.container;
	}
	

}

#endif