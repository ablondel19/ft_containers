/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:03:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/20 17:08:45 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	REVERSE_ITERATOR_HPP
#define	REVERSE_ITERATOR_HPP
#include <type_traits>
#include "iterator.hpp"

namespace ft
{
	template < class T >
	class random_access_reverse_iterator
	{
		private:
			T	*_it;
		public:
			typedef T*																					iterator_type;
			typedef typename	ft::iterator< random_access_reverse_iterator, T >::value_type			value_type;
			typedef typename	ft::iterator< random_access_reverse_iterator, T >::pointer				pointer;
			typedef typename	ft::iterator< random_access_reverse_iterator, T >::reference			reference;
			typedef typename	ft::iterator< random_access_reverse_iterator, T >::iterator_category	iterator_category;
			typedef typename	ft::iterator< random_access_reverse_iterator, T >::difference_type		difference_type;
		
		public:
			random_access_reverse_iterator() : _it(nullptr) {}
			random_access_reverse_iterator( T *it ) : _it(it) {}
			random_access_reverse_iterator( const random_access_reverse_iterator < typename remove_const<T>::type > &it ) : _it(it.base()) {}
			~random_access_reverse_iterator() {}

			
			random_access_reverse_iterator<T> &operator=(const random_access_reverse_iterator < typename remove_const< T >::type > &it )
			{
				_it = it.base();
				return *this;
			}

			reference operator*() const
			{
				return *(_it - 1);
			}

			iterator_type base() const
			{
				return _it;
			}

			pointer operator->() const
			{
				return *(_it - 1);
			}

			reference operator[](size_t n)
			{
				return *(_it - n - 1);
			}
			
			random_access_reverse_iterator& operator++()
			{
				--_it;
				return *this;
			}

			random_access_reverse_iterator operator++(int)
			{
				random_access_reverse_iterator tmp( *this );
				_it--;
				return tmp;
			}

			random_access_reverse_iterator& operator--()
			{
				_it++;
				return *this;
			}

			random_access_reverse_iterator operator--(int)
			{
				random_access_reverse_iterator tmp( *this );
				_it++();
				return tmp;
			}

			random_access_reverse_iterator operator+( difference_type n ) const
			{
				return random_access_reverse_iterator(base() - n);
			}

			difference_type	operator+( random_access_reverse_iterator const &x ) const
			{
				return (base() - x.base());
			}

			random_access_reverse_iterator operator-( difference_type n ) const
			{
				return random_access_reverse_iterator(base() + n);
			}

			difference_type	operator-( random_access_reverse_iterator const &x ) const
			{
				return (base() + x.base());
			}

			random_access_reverse_iterator &operator+=( difference_type n )
			{
				_it -= n;
				return *this;
			}

			random_access_reverse_iterator &operator-=( difference_type n )
			{
				_it += n;
				return *this;
			}
	};

	template < class it1, class it2 >
	bool operator==( const ft::random_access_reverse_iterator < it1 > &x, const ft::random_access_reverse_iterator < it2 > &y )	
	{
		return (x.base() == y.base());
	}
	
	template < class it1, class it2 >
	bool operator!=( const ft::random_access_reverse_iterator < it1 > &x, const ft::random_access_reverse_iterator < it2 > &y )	
	{
		return (x.base() != y.base());
	}

	template < class it1, class it2 >
	bool operator>=( const ft::random_access_reverse_iterator < it1 > &x, const ft::random_access_reverse_iterator < it2 > &y )	
	{
		return (x.base() <= y.base());
	}
	
	template < class it1, class it2 >
	bool operator<=( const ft::random_access_reverse_iterator < it1 > &x, const ft::random_access_reverse_iterator < it2 > &y )	
	{
		return (x.base() >= y.base());
	}

	template < class it1, class it2 >
	bool operator>( const ft::random_access_reverse_iterator < it1 > &x, const ft::random_access_reverse_iterator < it2 > &y )
	{
		return (x.base() < y.base());
	}
	
	template < class it1, class it2 >
	bool operator<( const ft::random_access_reverse_iterator < it1 > &x, const ft::random_access_reverse_iterator < it2 > &y )	
	{
		return (x.base() > y.base());
	}
	
};

#endif