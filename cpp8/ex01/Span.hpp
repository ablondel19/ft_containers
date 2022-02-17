/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:33:13 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/29 15:57:43 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <array>

class	Span
{
	private:
		unsigned			_n;
		std::vector<int>	_v;
		unsigned long long	_e;
		bool				_full;
		
	public:
		Span();
		Span( unsigned n );
		Span( const Span &obj );
		Span &operator=( const Span &obj );
		std::vector<int>	getVector( void ) const;
		unsigned			getSize( void ) const;
		void				addNumber( int value );
		int					random( int min, int max );
		void				addRange( int min, int max );
		unsigned			shortestSpan();
		unsigned			longestSpan();
		void				print( std::vector<int> V );
		~Span();
};

#endif