/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:03:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/27 11:33:51 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator.hpp"

namespace ft
{
	template < class T >
	class reverse_random_access_iterator
	{
		private:
			T	_rit;
		public:
			typedef T iterator_type;
			typedef typename T::value_type			value_type;
			typedef typename T::pointer				pointer;
			typedef typename T::reference			reference;
			typedef typename T::iterator_category	iterator_category;
			typedef typename T::difference_type		difference_type;

			reverse_random_access_iterator() : _rit() {}
			explicit reverse_random_access_iterator(iterator_type it) : _rit(it) {}
			explicit reverse_random_access_iterator(pointer p) : _rit(iterator_type(p)) {}
			template <class Iterator>
			reverse_random_access_iterator(const reverse_random_access_iterator<Iterator> & ref) : _rit(ref.base()) {}
			~reverse_random_access_iterator() {}

			reverse_random_access_iterator<T> & operator=(const reverse_random_access_iterator<typename ft::remove_const<T>::type > &obj)
			{
				_rit = obj.base();
				return (*this);
			}

			iterator_type base() const
			{
				return (_rit);
			}

			reference operator*() const
			{
				iterator_type	tmp = _rit;
				tmp--;
				return (*tmp);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reference operator[](size_t n)
			{
				return (*(_rit - n - 1));
			}

			reverse_random_access_iterator& operator++()
			{
				_rit--;
				return (*this);
			}

			reverse_random_access_iterator& operator--()
			{
				_rit++;
				return (*this);
			}

			reverse_random_access_iterator operator++( int )
			{
				reverse_random_access_iterator it = *this;
				_rit--;
				return (it);
			}
			reverse_random_access_iterator operator--( int )
			{
				reverse_random_access_iterator it = *this;
				_rit++;
				return (it);
			}
			reverse_random_access_iterator operator+( difference_type n ) const
			{
				return (reverse_random_access_iterator((base() - n)));
			}

			reverse_random_access_iterator operator-( difference_type n ) const
			{
				return (reverse_random_access_iterator((base() + n)));
			}

			difference_type		operator- (reverse_random_access_iterator const & b)
			{
				return (b._rit.base() - _rit.base());
			}

			reverse_random_access_iterator& operator+=( difference_type n )
			{
				_rit -= n;
				return (*this);
			}

			reverse_random_access_iterator& operator-=( difference_type n )
			{
				_rit += n;
				return (*this);
			}

	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_random_access_iterator<Iterator1>& lhs, const reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class T >
	reverse_random_access_iterator<T> operator+( typename reverse_random_access_iterator<T>::difference_type n, const reverse_random_access_iterator<T>& it )
	{
		return (reverse_random_access_iterator<T>(it.base() - n));
	}

	template< class T >
	reverse_random_access_iterator<T> operator-( typename reverse_random_access_iterator<T>::difference_type n, const reverse_random_access_iterator<T>& it )
	{
		return (reverse_random_access_iterator<T>(it.base() + n));
	}

	template < class T >
	size_t		operator-(reverse_random_access_iterator<T> const & a, reverse_random_access_iterator<T> const & b)
	{
		return (a.base() + b.base());
	}
};

#endif
