/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:47:04 by ablondel          #+#    #+#             */
/*   Updated: 2022/02/17 17:20:36 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <iostream>

namespace ft
{	
	template < class T, class A = std::allocator<T> >
	class	vector
	{
		private:
			T	*_data;
			size_t	_capacity;
			size_t	_nElements;
		protected:

		public:
			typedef T				value_type;
			typedef T*				pointer;
			typedef	const T*		const_pointer;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef std::size_t		size_type;
			//typedef T				*iterator;
			//typedef T				*const_iterator const;
			//typedef T				*reverse_iterator;
			//typedef T				*const_reverse_iterator const;
		
		//////////////
		// OPTIONAL //
		//////////////

		void	print() {
			for (size_t i = 0; i < _nElements; i++)
			{
				std::cout << _data[i] << " ";
			}
			std::cout << std::endl;
		};

		/////////////
		// GETTERS //
		/////////////

		T	*getVector() const {
			return _data;
		};

		size_type	getCapacity() const {
			return _capacity;
		};

		size_type	getnElements() const {
			return _nElements;
		};
		
		///////////////////////////////////////////////
		// CONSTRUCTORS DESTRUCTORS COPY ASSIGNATION //
		///////////////////////////////////////////////
			
			explicit vector() {
				_data = new T[1];
				_capacity = 1;
				_nElements = 0;
			};
			
			explicit vector( size_type n, const value_type& val = value_type() ) {
				_data = new T[n];
				_capacity = n;
				_nElements = n;
				for (size_t i = 0; i < n; i++)
					_data[i] = val;
			};
			
			//template <class InputIterator> vector( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() );
			
			//vector& operator=( const vector& x );
			
			//vector( const vector& x );
			
			~vector() {
				delete [] _data;
			};
		
		
		///////////////
		// ITERATORS //
		///////////////
			//iterator begin();
			//const_iterator begin() const;
			//iterator end();
			//const_iterator end() const;
			//reverse_iterator rbegin();
			//const_reverse_iterator rbegin() const;
			//reverse_iterator rend();
			//const_reverse_iterator rend() const;
		
		
		//////////////
		// CAPACITY //
		//////////////
			//size_type max_size() const;
			//void resize( size_type n, value_type val = value_type() );
			//size_type capacity() const;
			//bool empty() const;
			//void reserve( size_type n );
		
		
		////////////////////
		// ELEMENT ACCESS //
		////////////////////
			//reference operator[]( size_type n );
			//reference at( size_type n );
			//reference front();
			//const_reference front() const;
			//reference back();
			//const_reference back() const;
		
		
		///////////////
		// MODIFIERS //
		///////////////
			//template <class InputIterator> void assign ( InputIterator first, InputIterator last );
			//void assign ( size_type n, const value_type& val );
			//void push_back ( const value_type& val );
			//void pop_back();
			//iterator insert ( iterator position, const value_type& val );
			//void insert ( iterator position, size_type n, const value_type& val );
			//template <class InputIterator> void insert ( iterator position, InputIterator first, InputIterator last );
			//iterator erase ( iterator position );
			//iterator erase ( iterator first, iterator last );
			//void swap ( vector& x );
			//void clear();
	};
}

#endif