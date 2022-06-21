/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:03:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/20 08:36:46 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <memory>

namespace ft
{
	template < class U > struct remove_const 
	{
		typedef U type;
	};

	template < class U > struct remove_const < const U >
	{
		typedef U type;
	};
	
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
			random_access_iterator() : _it(nullptr) {}
			random_access_iterator( T *it ) : _it(it) {}
			random_access_iterator( const random_access_iterator < typename remove_const<T>::type > &it ) : _it(it.base()) {}
			~random_access_iterator() {}

			
			random_access_iterator<T> &operator=(const random_access_iterator < typename remove_const< T >::type > &it )
			{
				_it = it.base();
				return *this;
			}

			reference operator*() const
			{
				return *_it;
			}

			iterator_type base() const
			{
				return _it;
			}

			pointer operator->() const
			{
				return _it;
			}

			reference operator[](size_t n)
			{
				return (base()[n]);
			}
			
			random_access_iterator& operator++()
			{
				++_it;
				return *this;
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp( *this );
				operator++();
				return tmp;
			}

			random_access_iterator& operator--()
			{
				--_it;
				return *this;
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp( *this );
				operator--();
				return tmp;
			}

			random_access_iterator operator+( difference_type n ) const
			{
				return random_access_iterator(base() + n);
			}

			difference_type	operator+( random_access_iterator const &x ) const
			{
				return (base() + x.base());
			}

			random_access_iterator operator-( difference_type n ) const
			{
				return random_access_iterator(base() - n);
			}

			difference_type	operator-( random_access_iterator const &x ) const
			{
				return (base() - x.base());
			}

			random_access_iterator &operator+=( difference_type n )
			{
				_it += n;
				return *this;
			}

			random_access_iterator &operator-=( difference_type n )
			{
				_it -= n;
				return *this;
			}
	};

	template < class it1, class it2 >
	bool operator==( const ft::random_access_iterator < it1 > &x, const ft::random_access_iterator < it2 > &y )	
	{
		return (x.base() == y.base());
	}
	
	template < class it1, class it2 >
	bool operator!=( const ft::random_access_iterator < it1 > &x, const ft::random_access_iterator < it2 > &y )	
	{
		return (x.base() != y.base());
	}

	template < class it1, class it2 >
	bool operator>=( const ft::random_access_iterator < it1 > &x, const ft::random_access_iterator < it2 > &y )	
	{
		return (x.base() >= y.base());
	}
	
	template < class it1, class it2 >
	bool operator<=( const ft::random_access_iterator < it1 > &x, const ft::random_access_iterator < it2 > &y )	
	{
		return (x.base() <= y.base());
	}

	template < class it1, class it2 >
	bool operator>( const ft::random_access_iterator < it1 > &x, const ft::random_access_iterator < it2 > &y )
	{
		return (x.base() > y.base());
	}
	
	template < class it1, class it2 >
	bool operator<( const ft::random_access_iterator < it1 > &x, const ft::random_access_iterator < it2 > &y )	
	{
		return (x.base() < y.base());
	}
	
};

#endif
