/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:47:13 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/28 15:05:43 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include "iterator.hpp"
#include "pair.hpp"
#include "btree.hpp"
#include "map_iterator.hpp"
#include "map_reverse_iterator.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less< Key >, class Alloc = std::allocator< pair < const Key, T > > >
	class map
	{
		
		public:
			typedef Key																		key_type;
			typedef T																		mapped_type;
			typedef ft::pair< const key_type, mapped_type >									value_type;
			typedef Compare																	key_compare;
			typedef Alloc																	allocator_type;
			typedef value_type&																reference;
			typedef const value_type&														const_reference;
			typedef value_type*																pointer;
			typedef const value_type*														const_pointer;
			typedef ptrdiff_t																difference_type;
			typedef size_t																	size_type;
			typedef ft::subtree < const Key, T >											node;
			typedef typename ft::map_iterator < value_type, node >							iterator;
			typedef	ft::map_iterator < const value_type, node >								const_iterator;
			typedef ft::reverse_map_iterator < value_type, node >							reverse_iterator;
			typedef ft::reverse_map_iterator < const value_type, node >						const_reverse_iterator;
			typedef ft::btree < key_type, mapped_type, key_compare, allocator_type >		btree;
		
		private:
			class value_compare
			{
				protected:
					Compare comp;
				public:
					value_compare( Compare c ) : comp(c) {}
					bool operator()( const value_type& x, const value_type& y ) const { return comp(x.first, y.first); }
			};
			btree			_bst;
			key_compare 	_keycmp;
			allocator_type	_alloc;

/*///////////////////////////////////////////////////////////////////////////////////////////
//                    CONSTRUCTORS DESTRUCTORS COPY ASSIGNATION                            //
///////////////////////////////////////////////////////////////////////////////////////////*/

		public:
			/*---------------------------------------------------------------------------------------------------------------
			**	(1) Empty container constructor.
				Constructs an empty container, with no elements.
			*/
			explicit map( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ): _bst(btree()), _keycmp(comp), _alloc(alloc) {}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(2) Range constructor.
				Constructs a container, with as many elements as the range [first, last),
				with each element constructed from its corresponding element in that range.
			*/
			template <class InputIterator>
			map( InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type() ) : _bst(btree()), _keycmp(comp), _alloc(alloc)
			{
				while (first != last)
				{
					_bst.insert(ft::make_pair(first->first, first->second));
					++first;
				}
				return ;
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(3) Copy constructor.
				Constructs a container, with a copy of each of the elements in x.
			*/
			map( const map &x ) : _keycmp(x._keycmp), _alloc(x._alloc)
			{
				_bst = x._bst;
				return ;
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(1) Container destructor.
			*/
			~map() {}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(1) Copy operator.
				Copies all the elements from x into the container, chaging its size accordingly.
			*/
			map &operator=( const map &x )
			{
				clear();
				_bst = x._bst;
				_alloc = x._alloc;
				_keycmp = x._keycmp;
				return (*this);
			}
			
/*////////////////////////
//      ITERATORS       //
////////////////////////*/
			
			/*---------------------------------------------------------------------------------------------------------------
				(1) Returns an iterator referring to the first element in the map container.
				Because map containers keep their elements ordered at all times, begin points to the 
				element that goes first following the container's sorting criterion.
				If the container is empty, the returned iterator value shall not be dereferenced.
			*/
			iterator begin()
			{
				return (iterator(_bst.begin()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(2) An iterator to the first element in the container.
				If the map object is const-qualified, the function returns a const_iterator.
				Otherwise, it returns an iterator.
			*/
			const_iterator begin() const
			{
				return (const_iterator(_bst.begin()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(3) Returns an iterator referring to the past-the-end element in the map container.
				The past-the-end element is the theoretical element that would follow
				the last element in the map container. It does not point to any element, 
				and thus shall not be dereferenced. If the container is empty, 
				this function returns the same as map::begin.
			*/
			iterator end()
			{
				return (iterator(_bst.end()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(4) an iterator referring to the past-the-end element in the map container.
				If the map object is const-qualified, the function returns a const_iterator.
				Otherwise, it returns an iterator.
			*/
			const_iterator end() const
			{
				return (const_iterator(_bst.end()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(5) Returns a reverse iterator pointing to the last element in the container 
				(i.e., its reverse beginning). Reverse iterators iterate backwards: increasing them 
				moves them towards the beginning of the container.rbegin points to the element 
				preceding the one that would be pointed to by member end.
			*/
			reverse_iterator rbegin()
			{
				return (reverse_iterator(_bst.rbegin()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(6) A reverse iterator to the reverse beginning of the sequence container.
				If the map object is const-qualified, the function returns a const_reverse_iterator.
				Otherwise, it returns a reverse_iterator.
			*/
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_bst.rbegin()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(7) Returns a reverse iterator pointing to the theoretical element right before the first 
				element in the map container (which is considered its reverse end). The range between map::rbegin 
				and map::rend contains all the elements of the container (in reverse order).
			*/
			reverse_iterator rend()
			{
				return (reverse_iterator(_bst.rend()));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	(8) A reverse iterator to the reverse end of the sequence container.
				If the map object is const-qualified, the function returns a const_reverse_iterator.
				Otherwise, it returns a reverse_iterator.
			*/
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(_bst.rend()));
			}

/*///////////////////////
//      CAPACITY       //
///////////////////////*/
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns whether the map container is empty (i.e. whether its size is 0).
			*/
			bool empty() const
			{
				return (!_bst.size());
			}

			/*---------------------------------------------------------------------------------------------------------------
			**	Returns the number of elements in the container.
			*/
			size_type size() const
			{
				return (_bst.size());
			}

			/*---------------------------------------------------------------------------------------------------------------
			**	Returns the maximum number of elements that the map container can hold.
				This is the maximum potential size the container can reach due to known 
				system or library implementation limitations, but the container is 
				by no means guaranteed to be able to reach that size: it can still fail 
				to allocate storage at any point before that size is reached.
			*/
			size_type max_size() const
			{
				return (_alloc.max_size());
			}
			
/*///////////////////////
//   ELEMENT ACCESS    //
///////////////////////*/

			/*---------------------------------------------------------------------------------------------------------------
			**	If k matches the key of an element in the container, the function returns 
				a reference to its mapped value. If k does not match the key of any element 
				in the container, the function inserts a new element with that key and returns 
				a reference to its mapped value. Notice that this always increases the container 
				size by one, even if no mapped value is assigned to the element 
				(the element is constructed using its default constructor).
			*/
			mapped_type& operator[]( const key_type& k )
			{
				return (*((insert(ft::make_pair(k,mapped_type()))).first)).second;
			}

			/*---------------------------------------------------------------------------------------------------------------
			**	Returns a reference to the mapped value of the element identified with key k.
				If k does not match the key of any element in the container, the function 
				throws an out_of_range exception.
			*/
			mapped_type& at(const key_type& k)
			{
				if (!_bst.search(k))
					throw(std::out_of_range("map"));
				return operator[](k);
			}

			/*---------------------------------------------------------------------------------------------------------------
			**	A reference to the mapped value of the element with a key value equivalent to k.
				If the map object is const-qualified, the function returns a reference to const mapped_type. 
				Otherwise, it returns a reference to mapped_type.
			*/
			const mapped_type& at(const key_type& k) const
			{
				if (!_bst.search(k))
					throw(std::out_of_range("map"));
				return operator[](k);
			}

/*///////////////////////
//      MODIFIERS      //
///////////////////////*/

			/*---------------------------------------------------------------------------------------------------------------
			**	The single element version return a pair, with its member pair::first set to 
				an iterator pointing to either the newly inserted element or to the element 
				with an equivalent key in the map. The pair::second element in the pair is 
				set to true if a new element was inserted or false if an equivalent key 
				already existed.
			*/
			pair<iterator, bool> insert( const value_type& val )
			{
				return (_bst.insert(val));
			}

			/*---------------------------------------------------------------------------------------------------------------
			**	The versions with a position iterator returns an iterator pointing to either 
				the newly inserted element or to the element that already had an equivalent 
				key in the map.
			*/
			iterator insert( iterator position, const value_type &val )
			{
				(void)position;
				ft::pair < iterator, bool > tmp = _bst.insert(val);
				return (tmp.first);
			}

			/*---------------------------------------------------------------------------------------------------------------
			**	Iterators specifying a range of elements. Copies of the elements in the range 
				[first,last) are inserted in the container. The range includes all the elements 
				between first and last, including the element  pointed by first but not the one 
				pointed by last.
			*/
			template < class InputIterator >
			void insert( InputIterator first, InputIterator last )
			{
				for (;first != last; ++first)
					_bst.insert(ft::make_pair(first->first, first->second));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Removes the element at the specified position from the container.
			*/
			void erase( iterator position )
			{
				key_type tmp = position->first;
				_bst.erase(tmp);
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Removes the element corresponding to the key from the container.
			*/
			size_type erase( const key_type &k )
			{
				return (_bst.erase(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Remove all the elements in the range [first,last).
			*/
			void erase( iterator first, iterator last )
			{
				_bst.clear(first, last);
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Exchanges the content of the container by the content of x, 
				which is another map of the same type.
			*/
			void swap( map &x )
			{
				key_compare tmp = x._keycmp;
				x._keycmp = _keycmp;
				_keycmp = tmp;
				allocator_type tmp2 = x._alloc;
				x._alloc = _alloc;
				_alloc = tmp2;
				_bst.swap(x._bst);
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Removes all elements from the map container (which are destroyed),
				leaving the container with a size of 0.
			*/
			void clear()
			{
				_bst.clear(begin(), end());
			}
		
/*//////////////////////
//     OBSERVERS      //
//////////////////////*/

			/*---------------------------------------------------------------------------------------------------------------
			**	Returns a copy of the comparison object used by the container to compare keys.
			*/
			key_compare key_comp() const
			{
				key_compare copy = _keycmp;
				return (copy);
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns a comparison object that can be used to compare two elements to get 
				whether the key of the first one goes before the second.
			*/
			value_compare value_comp() const
			{
				return (value_compare(_keycmp));
			}

/*//////////////////////
//     OPERATIONS     //
//////////////////////*/

			/*---------------------------------------------------------------------------------------------------------------
			**	Searches the container for an element with a key equivalent to k and returns 
				an iterator to it if found, otherwise it returns an iterator to map::end.
			*/
			iterator find( const key_type &k )
			{
				return (_bst.find(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Searches the container for an element with a key equivalent to k and returns 
				an iterator to it if found, otherwise it returns an iterator to map::end.
				If the map object is const-qualified, the function returns a const_iterator.
				Otherwise, it returns an iterator.
			*/
			const_iterator find( const key_type &k ) const
			{
				return (_bst.find(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Searches the container for elements with a key equivalent to k and returns 
				the number of matches. Because all elements in a map container are unique, 
				the function can only return 1 (if the element is found) or zero (otherwise).
			*/
			size_type count( const key_type &k ) const
			{
				return (_bst.count(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns an iterator pointing to the first element in the container whose key 
				is not considered to go before k (i.e., either it is equivalent or goes after).
			*/
			iterator lower_bound( const key_type &k )
			{
				return (_bst.lower_bound(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns an iterator pointing to the first element in the container whose key 
				is not considered to go before k (is equivalent or goes after).
				If the map object is const-qualified, the function returns a const_iterator. 
				Otherwise, it returns an iterator.
			*/
			const_iterator lower_bound( const key_type &k ) const
			{
				return (_bst.lower_bound(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns an iterator pointing to the first element in the container whose key 
				is considered to go after k.
			*/
			iterator upper_bound( const key_type &k )
			{
				return (_bst.upper_bound(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns an iterator pointing to the first element in the container whose key 
				is considered to go after k. If the map object is const-qualified, the function 
				returns a const_iterator. Otherwise, it returns an iterator.
			*/
			const_iterator upper_bound( const key_type &k ) const
			{
				return (_bst.upper_bound(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns the bounds of a range that includes all the elements in the container 
				which have a key equivalent to k. Because the elements in a map container have 
				unique keys, the range returned will contain a single element at most.
			*/
			pair < const_iterator, const_iterator > equal_range( const key_type &k ) const
			{
				return (_bst.equal_range(k));
			}
			
			/*---------------------------------------------------------------------------------------------------------------
			**	Returns the bounds of a range that includes all the elements in the container 
				which have a key equivalent to k. Because the elements in a map container have 
				unique keys, the range returned will contain a single element at most.
			*/
			pair < iterator, iterator > equal_range( const key_type &k )
			{
				return (_bst.equal_range(k));
			}

/*///////////////////////
//      ALLOCATOR      //
///////////////////////*/

			/*---------------------------------------------------------------------------------------------------------------
			**	Returns a copy of the allocator object associated with the map.
			*/
			allocator_type get_allocator() const
			{
				allocator_type copy = _alloc;
				return (copy);
			}
			
	};

/*///////////////////////
//      OVERLOADS      //
///////////////////////*/

	/*---------------------------------------------------------------------------------------------------------------
	**	Performs the appropriate comparison operation between the map containers lhs and rhs.
	*/
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T>::const_iterator it = lhs.begin(), rit = rhs.begin(), end = lhs.end(), rend = rhs.end();
		while (it != end && rit != rend)
		{
			if (*it != *rit)
				return (0);
			it++;
			rit++;
		}
		if (rhs.size() == lhs.size())
			return (1);
		return (0);
	}
	
	template< class Key, class T, class Compare, class Alloc > 
	bool operator!=( const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs )
	{
		return (!(lhs == rhs));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs )
	{
		return (!(rhs < lhs));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs )
	{
		return (rhs < lhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs )
	{
		return (!(lhs < rhs));
	}
	
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc> &lhs, ft::map<Key,T,Compare,Alloc> &rhs )
	{
		lhs.swap(rhs);
	}
	
}

#endif