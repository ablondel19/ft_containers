/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:03:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/27 11:34:46 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include <iostream>
#include <memory>
#include <type_traits>

namespace ft
{
	template< class T2 > struct remove_const{typedef T2 type; };	
	template< class T2 > struct remove_const<const T2>{ typedef T2 type; };

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class U>
	class reverse_random_iterator;

	template < class T >
	class random_access_iterator
	{
		private:
			T*	_it;
		public:
			typedef T* iterator_type;
			typedef typename ft::iterator<random_access_iterator, T>::value_type			value_type;
			typedef typename ft::iterator<random_access_iterator, T>::pointer				pointer;
			typedef typename ft::iterator<random_access_iterator, T>::reference			reference;
			typedef typename ft::iterator<random_access_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_access_iterator, T>::difference_type		difference_type;

			random_access_iterator( void ) : _it(NULL) {}
			random_access_iterator( const random_access_iterator<typename remove_const<T>::type > & obj ) : _it(obj.base()) {}
			random_access_iterator( const reverse_random_iterator<typename remove_const<T>::type > & obj ) : _it(obj.base()) {}
			random_access_iterator( pointer pointer ) : _it(pointer) {}
			~random_access_iterator() {}

			random_access_iterator<T> & operator=(const random_access_iterator<typename ft::remove_const<T>::type > &obj)
			{
				_it = obj.base();
				return (*this);
			}

			iterator_type base() const
			{
				return (_it);
			}

			reference operator*() const
			{
				return (*_it);
			}

			pointer operator->() const
			{
				return (_it);
			}

			reference operator[](size_t n)
			{
				return (base()[n]);
			}

			random_access_iterator& operator++()
			{
				_it++;
				return (*this);
			}

			random_access_iterator& operator--()
			{
				_it--;
				return (*this);
			}

			random_access_iterator operator++( int )
			{
				random_access_iterator it = *this;
				_it++;
				return (it);
			}
			random_access_iterator operator--( int )
			{
				random_access_iterator it = *this;
				_it--;
				return (it);
			}
			random_access_iterator operator+( difference_type n ) const
			{
				return (random_access_iterator((base() + n)));
			}

			random_access_iterator operator-( difference_type n ) const
			{
				return (random_access_iterator(base() - n));
			}

			difference_type		operator- (random_access_iterator const & b)
			{
				return (base() - b.base());
			}

			random_access_iterator& operator+=( difference_type n )
			{
				_it += n;
				return (*this);
			}

			random_access_iterator& operator-=( difference_type n )
			{
				_it -= n;
				return (*this);
			}

	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iter >
	random_access_iterator<Iter> operator+( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it )
	{
		return (random_access_iterator<Iter>(it.base() + n));
	}

	template < class T >
	size_t		operator-(random_access_iterator<T> const & a, random_access_iterator<T> const & b)
	{
		return (a.base() - b.base());
	}

	template< class Iter >
	random_access_iterator<Iter> operator-( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it )
	{
		return (random_access_iterator<Iter>(it.base() - n));
	}
};

#endif
