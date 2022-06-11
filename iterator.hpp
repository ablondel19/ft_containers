/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:03:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/11 02:40:22 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <memory>
#include <type_traits>

namespace ft
{
	
	template < class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template < class T >
	class random_access_iterator
	{
		private:
			T	*_it;
		public:
			typedef T*																			iterator_type;
			typedef typename	ft::iterator< random_access_iterator, T >::value_type			value_type;
			typedef typename	ft::iterator< random_access_iterator, T >::pointer				pointer;
			typedef typename	ft::iterator< random_access_iterator, T >::reference			reference;
			typedef typename	ft::iterator< random_access_iterator, T >::iterator_category	iterator_category;
			typedef typename	ft::iterator< random_access_iterator, T >::difference_type		difference_type;
		
		public:
			random_access_iterator() : _it(NULL) {};
			random_access_iterator( T *it ) : _it(it) {};
			random_access_iterator( const random_access_iterator &it ) : _it(it.base()) {};
			~random_access_iterator() {};

			reference operator*() const	{
				return *_it;
			}

			iterator_type base() const	{
				return _it;
			}

			random_access_iterator<T> &operator=(const random_access_iterator<T> &obj)
			{
				_it = obj.base();
				return *this;
			}

			pointer operator->() const	{
				return _it;
			}

			reference operator[](size_t n)	{
				return (base()[n]);
			}
			
			random_access_iterator& operator++()	{
				++_it;
				return *this;
			}

			random_access_iterator operator++(int)	{
				random_access_iterator tmp( *this );
				operator++();
				return tmp;
			}

			random_access_iterator& operator--()	{
				--_it;
				return *this;
			}

			random_access_iterator operator--(int)	{
				random_access_iterator tmp( *this );
				operator--();
				return tmp;
			}

			random_access_iterator operator+( difference_type n ) const	{
				return (base() + n);
			}

			random_access_iterator operator-( difference_type n ) const	{
				return (base() - n);
			}

			random_access_iterator &operator+=( difference_type n )	{
				_it += n;
				return *this;
			}

			random_access_iterator &operator-=( difference_type n )	{
				_it -= n;
				return *this;
			}
	};

	template < class T >
	bool operator==( const ft::random_access_iterator < T > &x, const ft::random_access_iterator < T > &y )	
	{
		return (x.base() == y.base());
	}
	
	template < class T >
	bool operator!=( const ft::random_access_iterator < T > &x, const ft::random_access_iterator < T > &y )	
	{
		return (x.base() != y.base());
	}

	template < class T >
	bool operator>=( const ft::random_access_iterator < T > &x, const ft::random_access_iterator < T > &y )	
	{
		return (x.base() >= y.base());
	}
	
	template < class T >
	bool operator<=( const ft::random_access_iterator < T > &x, const ft::random_access_iterator < T > &y )	
	{
		return (x.base() <= y.base());
	}

	template < class T >
	bool operator>( const ft::random_access_iterator < T > &x, const ft::random_access_iterator < T > &y )	
	{
		return (x.base() > y.base());
	}
	
	template < class T >
	bool operator<( const ft::random_access_iterator < T > &x, const ft::random_access_iterator < T > &y )	
	{
		return (x.base() < y.base());
	}
	
};

#endif
