/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:47:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/28 11:15:27 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	https://cdn.intra.42.fr/pdf/pdf/34895/fr.subject.pdf
**	https://www.cplusplus.com/reference/vector/vector/
**	https://anderberg.me/2016/07/04/c-custom-iterators/
**	https://stackoverflow.com/questions/21275190/c-custom-collection-reverse-iterator-with-similar-behaviour-to-stdvector-imp
**	https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/
**  https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/
**  https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/
**  https://www.fluentcpp.com/2018/04/27/tag-dispatching/
*/

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <exception>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"

#define ITERATOR_TYPE ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*
namespace ft
{
	template <class T, class Alloc=std::allocator<T> >
	class	vector
	{
		public:
			typedef size_t													size_type;
			typedef ft::random_access_iterator<T>							iterator;
			typedef ft::random_access_iterator<const T>						const_iterator;
			typedef ft::reverse_random_access_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_random_access_iterator<const_iterator>		const_reverse_iterator;
			typedef Alloc													allocator_type;
			typedef T														value_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename Alloc::pointer									pointer;
			typedef typename Alloc::const_pointer							const_pointer;
			typedef ptrdiff_t												difference_type;

		private:
			allocator_type	_alloc;
			size_t			_size; 
			size_t			_capacity;
			value_type		*_v;

	/*
	** MEMBER FUNCTIONS
	*/
		///////////////////////////////////////////////
		// CONSTRUCTORS DESTRUCTORS COPY ASSIGNATION //
		///////////////////////////////////////////////
		public:
			explicit vector( const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _size(0), _capacity(0)
			{
				_v = _alloc.allocate(0);
			}
			
			explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _size(n), _capacity(n), _v(_alloc.allocate(n))
			{
				if (n < 0)
					throw (std::length_error("vector"));
				for (size_t i = 0; i < n; ++i)
					_alloc.construct(&_v[i], val);
			}
			
			template <class InputIterator>
         	vector( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ITERATOR_TYPE = nullptr ) : _alloc(alloc), _size(0), _capacity(0)
			{
				for (InputIterator tmp = first; tmp != last; ++tmp, ++_size, ++_capacity);
				_v = _alloc.allocate(_size);
				for (size_t i = 0; i < _size; ++i, ++first)
					_alloc.construct(&_v[i], *first);
			}
			
			vector( const vector& x ) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_v = _alloc.allocate(x._capacity);
				for (size_t i = 0; i < _size; ++i)
					_alloc.construct(&_v[i], x._v[i]);
			}

			vector &operator=( const vector &x )
			{
				for (size_t i = 0; i < _size; ++i)
					_alloc.destroy(&_v[i]);
				_alloc.deallocate(_v, _capacity);
				_alloc = x._alloc;
				_capacity = x._capacity;
				_size = x._size;
				_v = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; ++i)
					_alloc.construct(&_v[i], x._v[i]);
				return *this;
			}

			~vector()
			{
				for (; _size; --_size)
					_alloc.destroy(&_v[_size]);
				_alloc.deallocate(_v, _capacity);
			}

		//////////////
		// ITERATOR //
		//////////////

			iterator begin()
			{
				return (iterator(_v));
			}
			
			const_iterator begin() const
			{
				return (const_iterator(_v));
			}
			
			iterator end()
			{
				if (!_size)
					return begin();
				return (iterator(_v + _size));
			}
			
			const_iterator end() const
			{
				if (!_size)
					return begin();
				return (const_iterator(_v + _size));
			}
			
			reverse_iterator rbegin()
			{
				return (reverse_iterator(_v + _size));
			}
			
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_v + _size));
			}
			
			reverse_iterator rend()
			{
				return (reverse_iterator(_v));
			}
			
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(_v));
			}
			
		
		//////////////
		// CAPACITY //
		//////////////

			size_t size() const
			{
				return _size;
			}

			size_t max_size() const
			{
				return (_alloc.max_size());
			}

			void resize( size_type n, value_type val = value_type() )
			{
				if (n == _size)
					return ;
				if (n < _size)
				{
					for (size_t i = n; i < _size; ++i)
						_alloc.destroy(&_v[i]);
					_size = n;
					return ;
				}
				else if (n > _capacity || n > _size)
					reserve(n);
				for (size_t i = _size; i < n; ++i)
					_alloc.construct(&_v[i], val);
				_size = n;
			}
			
			size_type capacity() const
			{
				return _capacity;
			}
			
			bool empty() const
			{
				return (!_size);
			}
			
			void reserve( size_type n )
			{
				if (n < _capacity)
					return ;
				else if (n > max_size())
					throw(std::length_error("vector"));
				pointer tmp = _v;
				_v = _alloc.allocate(n);
				for (size_t i = 0; i < _size; ++i)
				{
					_alloc.construct(&_v[i], tmp[i]);
					_alloc.destroy(&tmp[i]);
				}
				_alloc.deallocate(tmp, _capacity);
				_capacity = n;
			}
		
		////////////////////
		// ELEMENT ACCESS //
		////////////////////

			reference operator[]( size_t n )
			{
				return _v[n];
			}
			
			const_reference operator[]( size_t n ) const
			{
				return _v[n];
			}
			
			reference at( size_t n )
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return _v[n];
			}
			
			const_reference	at( size_t n ) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return _v[n];
			}
			
			reference front()
			{
				return _v[0];
			}
			
			const_reference	front() const
			{
				return _v[0];
			}
			
			reference back()
			{
				return _v[_size - 1];
			}
			
			const_reference	back() const
			{
				return _v[_size - 1];
			}
		
		///////////////
		// MODIFIERS //
		///////////////
		
			template <class InputIterator>
			void assign( InputIterator first, InputIterator last, typename ITERATOR_TYPE = nullptr )
			{
				size_t n = 0;
				
				for (InputIterator tmp = last; tmp != first; --tmp)
					n++;
				reserve(n);
				resize(0);
				_size = n;
				for (; first != last; first++, --n)
					_alloc.construct(&_v[_size - n], *first);
			}
			
			void assign( size_type n, const value_type& val )
			{
				reserve(n);
				_size = n;
				for (size_t i = 0; i < n; ++i)
					_alloc.construct(&_v[i], val);
			}
			
			void push_back( const value_type& val )
			{
				size_t n;
				
				if (_size >= _capacity)
				{
					n = (_capacity == 0) ? 2 : _capacity * 2;
					reserve(n);
				}
				_alloc.construct(&_v[_size++], val);
			}
			
			void pop_back()
			{
				if (!_size)
					return ;
				resize(_size - 1);
			}
			
			iterator insert( iterator position, const value_type& val )
			{
				size_t i = 0;
				size_t j = _size;
				
				for (iterator tmp = begin(); tmp < position; ++tmp)
					++i;
				reserve(_size + 1);
				_size += 1;
				for (; j > i; --j)
					_v[j] = _v[j - 1];
				_alloc.construct(&_v[i], val);
				return iterator(&_v[i]);
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_t i = 0;
				size_t j = _size + n - 1;
				
				for (iterator it = begin(); it < position; it++)
					i++;
				reserve(n + _size);
				_size += n;
				for (;j >= n + i; j--)
					_v[j] = _v[j - n];
				for (;j > i && j != 0; j--)
					_alloc.construct(_v + j, val);
				if (j >= i)
					_alloc.construct(_v + j, val);
				return ;
			}
			
			template <class InputIterator> 
			void insert( iterator position, InputIterator first, InputIterator last, typename ITERATOR_TYPE = nullptr )
			{
				size_t i = 0;
				size_t gap = 0;
				size_t j = 0;

				for (InputIterator tmp = first; tmp != last; ++tmp)
					j++;
				for (iterator tmp = begin(); tmp != position; ++tmp)
					gap++;
				reserve(_size + j);
				position = begin() + gap;
				for (iterator tmp = end() + j - 1; tmp >= position + j; --tmp)
					*tmp = *(tmp - j);
				for (InputIterator tmp = first; tmp != last; ++tmp, ++i)
					_alloc.construct(&position[i], *(tmp));
				_size += j;
			}

			iterator erase( iterator position )
			{
				size_t i = 0;
				iterator tmp = position;
				
				for (iterator it = begin(); it < position; ++it, ++i)
					_alloc.destroy(&_v[i]);
				for (; position + 1 < end(); ++position)
					*position = *(position + 1);			
				_size -= 1;
				return (tmp);
			}
			
			iterator erase( iterator first, iterator last )
			{
				size_t i = 0;
				size_t gap = last - first;
				
				for (iterator it = begin(); it < last; ++it)
					i++;
				for (; first < last; --last, --i)
					_alloc.destroy(&_v[i]);
				for (size_t i = 0; end() > first + gap + i; ++i)
					*(first + i) = *(first + gap + i);
				resize(_size - gap);
				return (first);
			}
			
			void swap( vector& x )
			{
				Alloc		new_alloc;
				size_t		new_size;
				size_t		new_capacity;
				value_type	*tmp;
				
				new_alloc = x._alloc;
				new_capacity = x._capacity;
				new_size = x._size;
				tmp = x._v;
				x._alloc = _alloc;
				x._capacity = _capacity;
				x._size = _size;
				x._v = _v;
				_alloc = new_alloc;
				_capacity = new_capacity;
				_size = new_size;
				_v = tmp;
			}
			
			void clear()
			{
				for (size_t i = 0; i != _size; ++i)
					_alloc.destroy(&_v[i]);
				_size = 0;
			}

		///////////////
		// ALLOCATOR //
		///////////////
			
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
	};
	
	/*
	** NON MEMBER FUNCTIONS
	*/
	
		///////////////
		// 	 SWAP    //
		///////////////
			
			template < class T, class Alloc >
			void swap( vector < T, Alloc > &x, vector < T, Alloc > &y )
			{
				vector < T, Alloc > tmp;
				tmp = x;
				x = y;
				y = tmp;
			}
		
		///////////////
		// OPERATORS //
		///////////////
		
			template < class T, class Alloc >
			bool operator==( const vector < T, Alloc > &lhs, const vector < T, Alloc > &rhs )
			{
				if (lhs.size() == rhs.size())
				{
					for (size_t i = 0; i < rhs.size(); i++)
						if (rhs[i] != lhs[i])
							return 0;
					return 1;
				}
				return 0;
			}

			template < class T, class Alloc >
			bool operator!=( const vector < T, Alloc > &lhs, const vector < T, Alloc > &rhs )
			{
				if (lhs.size() == rhs.size())
				{
					for (size_t i = 0; i < rhs.size(); i++)
						if (rhs[i] != lhs[i])
							return 1;
					return 0;
				}
				return 1;
			}

			template < class T, class Alloc >
			bool operator<( const vector < T, Alloc > &lhs, const vector < T, Alloc > &rhs )
			{
				for (size_t i = 0; i < lhs.size() && i < rhs.size(); i++)
				{
					if (rhs[i] < lhs[i])
						return 0;
					else if (lhs[i] < rhs[i])
						return 1;
				}
				return (lhs.size() < rhs.size());
			}

			template < class T, class Alloc >
			bool operator>( const vector < T, Alloc > &lhs, const vector < T, Alloc > &rhs )
			{
				for (size_t i = 0; i < lhs.size() && i < rhs.size(); i++)
				{
					if (rhs[i] > lhs[i])
						return 0;
					else if (lhs[i] > rhs[i])
						return 1;
				}
				return (lhs.size() > rhs.size());
			}

			template < class T, class Alloc >
			bool operator<=( const vector < T, Alloc > &lhs, const vector < T, Alloc > &rhs )
			{
				return (lhs == rhs || lhs < rhs);
			}

			template < class T, class Alloc >
			bool operator>=( const vector < T, Alloc > &lhs, const vector < T, Alloc > &rhs )
			{
				return (lhs == rhs || lhs > rhs);
			}
}

#endif