/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:39:38 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/29 16:07:26 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

void	Span::print( std::vector<int> V )
{
	for (size_t i = 0; i < _n; i++)
		std::cout << "[" << V[i] << "]";
	std::cout << std::endl;
}

Span::Span()
{
	//std::cout << "__Span Default constructor__" << std::endl;
}

Span::Span( unsigned n ) : _n(n), _e(1), _full(false)
{
	//std::cout << "__Span Parametric constructor__" << std::endl;
	_v.reserve(_n);
}

Span::Span( const Span &obj )
{
	//std::cout << "__Span Copy constructor__" << std::endl;
	*this = obj;
}

Span			&Span::operator=( const Span &obj )
{
	//std::cout << "__Span Assignation operator__" << std::endl;
	_n = obj.getSize();
	_v.reserve(_n);
	for (size_t i = 0; i < _n; i++)
		_v.push_back(obj._v[i]);
	return (*this);
}

std::vector<int> Span::getVector() const
{
	return _v;
}

unsigned		Span::getSize() const
{
	return _n;
}

void 			Span::addNumber( int value )
{
	if (_full == false)
	{
		if (_e > _n)
		{
			std::cout << "Max capacity has been reached" << std::endl;
			_full = true;
			return ;
		}
		_v.push_back(value);
		_e++;
	}
}

int				Span::random( int min, int max )
{
	static bool first = true;
	if (first)
	{
		srand( time(NULL) );
		first = false;
	}
	return min + rand() % (( max + 1 ) - min);
}

void 			Span::addRange( int min, int max )
{
	if (_full == false)
	{
		for (size_t i = 0; i < _n; i++)
		{
			if (_e > _n)
			{
				std::cout << "Max capacity has been reached" << std::endl;
				_full = true;
				return ;
			}
			int value = random(min, max);
			_v.push_back(value);
			_e++;
		}
	}
}

unsigned		Span::longestSpan()
{
	if (_n <= 1)
	{
		std::cout << "No span can be found in this container" << std::endl;
		return 0;
	}
	//print(_v);
	int max = *std::max_element(_v.begin(), _v.end());
	int min = *std::min_element(_v.begin(), _v.end());
	std::cout << "Longest span is between values " << min << " & " << max << " and is equal to " << std::abs(max - min) << std::endl;
	return std::abs(max - min);
}

unsigned		Span::shortestSpan()
{
	int b = 0;
	int e = 0;
	int s = INT_MAX;
	int sp = INT_MAX;
	std::vector<int> clone;

	if (_n <= 1)
	{
		std::cout << "No span can be found in this container" << std::endl;
		return 0;
	}
	clone.reserve(_n);
	for (size_t i = 0; i < _n; i++)
		clone.push_back(_v[i]);
	//std::cout << "ORGINAL" << std::endl;
	//print(_v);
	//std::cout << "CLONE" << std::endl;
	//print(clone);
	std::sort(clone.begin(), clone.end());
	//std::cout << "SORTED CLONE" << std::endl;
	//print(clone);
	for (size_t i = 1; i < clone.size(); i++)
	{
		//std::cout << "[" << clone[i] - clone[i - 1] << "]";
		s = clone[i] - clone[i - 1];
		if (s > 0 && s < sp)
		{
			sp = s;
			e = clone[i - 1];
			b = clone[i];
		}
	}
	std::cout << "shortest span is between values " << e << " & " << b << " and is equal to " << std::abs(sp) << std::endl;
	return std::abs(sp);
}

Span::~Span()
{
	//std::cout << "__Span Default destructor__" << std::endl;
}
