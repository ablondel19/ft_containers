/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:50 by ablondel          #+#    #+#             */
/*   Updated: 2022/02/17 16:10:15 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://cdn.intra.42.fr/pdf/pdf/34895/fr.subject.pdf
https://www.cplusplus.com/reference/vector/vector/
https://anderberg.me/2016/07/04/c-custom-iterators/
https://stackoverflow.com/questions/21275190/c-custom-collection-reverse-iterator-with-similar-behaviour-to-stdvector-imp
https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/


vector class

	vector() // vector constructor
		
		(1) empty container constructor; 
			explicit vector (const allocator_type& alloc = allocator_type());
		(2) fill constructor; 
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		(3) range constructor; 
			template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		(4) copy constructor; 
			vector (const vector& x);
	
			alloc: Allocator object.
			The container keeps and uses an internal copy of this allocator.
			Member type allocator_type is the internal allocator type used by the container, defined in vector as an alias of its second template parameter (Alloc).
			If allocator_type is an instantiation of the default allocator (which has no state), this is not relevant.

			n: Initial container size (i.e., the number of elements in the container at construction).

			val: Value to fill the container with.
			Each of the n elements in the container will be initialized to a copy of this value.
			Member type value_type is the type of the elements in the container, defined in vector as an alias of its first template parameter (T).

			first, last: Input iterators to the initial and final positions in a range. 
			The range used is [first,last), which includes all the elements between first and last, including the element pointed by first but not the element pointed by last.
			The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.

			x: Another vector object of the same type
			(with the same class template arguments T and Alloc), whose contents are either copied or acquired.

	~vector // vector destructor
	This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.

	operator= // assign content
		vector& operator= (const vector& x);
		Copies all the elements from x into the container. The container preserves its current allocator, which is used to allocate storage in case of reallocation.
			x: A vector object of the same type (i.e., with the same template parameters, T and Alloc).
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ITERATORS //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	begin // return iterator to beginning
		iterator begin();
		const_iterator begin() const;
			Returns an iterator pointing to the first element in the vector.
			Notice that, unlike member vector::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
			If the container is empty, the returned iterator value shall not be dereferenced.
			An iterator to the beginning of the sequence container.
			If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
			Member types iterator and const_iterator are random access iterator types (pointing to an element and to a const element, respectively).

	end // return iterator to end 
		iterator end();
		const_iterator end() const;
			Returns an iterator referring to the past-the-end element in the vector container.
			The past-the-end element is the theoretical element that would follow the last element in the vector. 
			It does not point to any element, and thus shall not be dereferenced.
			Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, 
			this function is often used in combination with vector::begin to specify a range including all the elements in the container.
			If the container is empty, this function returns the same as vector::begin.
	
	rbegin // return reverse iterator to beginning
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
			Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
			Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			rbegin points to the element right before the one that would be pointed to by member end.
			Notice that unlike member vector::back, which returns a reference to this same element, this function returns a reverse random access iterator.
			A reverse iterator to the reverse beginning of the sequence container.
			If the vector object is const-qualified, the function returns a const_reverse_iterator. Otherwise, it returns a reverse_iterator.
			Member types reverse_iterator and const_reverse_iterator are reverse random access iterator types (pointing to an element and to a const element, respectively). See vector member types.

	rend // return reverse iterator to end
		reverse_iterator rend();
		const_reverse_iterator rend() const;
			Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
			The range between vector::rbegin and vector::rend contains all the elements of the vector (in reverse order).
			A reverse iterator to the reverse end of the sequence container.
			If the vector object is const-qualified, the function returns a const_reverse_iterator. Otherwise, it returns a reverse_iterator.
			Member types reverse_iterator and const_reverse_iterator are reverse random access iterator types (pointing to an element and to a const element, respectively). See vector member types.

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CAPACITY //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	size // return size of the vector
		size_type size() const;
			This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
	
	max_size // return maximum size of the vector 
		size_type max_size() const;
			Returns the maximum number of elements that the vector can hold.
			This is the maximum potential size the container can reach due to known system or library implementation limitations, 
			but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.

	resize // change size
		void resize (size_type n, value_type val = value_type());
			Resizes the container so that it contains n elements.
			If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
			If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. 
			If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			If a reallocation happens, the storage is allocated using the container's allocator, which may throw exceptions on failure 
			(for the default allocator, bad_alloc is thrown if the allocation request does not succeed).
				n: New container size, expressed in number of elements. Member type size_type is an unsigned integral type.
				val: Object whose content is copied to the added elements in case that n is greater than the current container size. 
				If not specified, the default constructor is used instead.
				Member type value_type is the type of the elements in the container, defined in vector as an alias of the first template parameter (T).
				Notice that this function changes the actual content of the container by inserting or erasing elements from it.
	
	capacity // return size of allocated storage capacity 
		size_type capacity() const;
			Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
			This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
			Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, 
			it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
			The capacity of a vector can be explicitly altered by calling member vector::reserve.
	
	empty // test whether the vector is empty 
		bool empty() const;
			Returns whether the vector is empty (i.e. whether its size is 0).

	reserve // request a change in capacity
		void reserve (size_type n);
				n: Minimum capacity for the vector. Note that the resulting vector capacity may be equal or greater than n. Member type size_type is an unsigned integral type.
			Requests that the vector capacity be at least enough to contain n elements.
			If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
			In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
			This function has no effect on the vector size and cannot alter its elements.
			If the size requested is greater than the maximum size (vector::max_size), a length_error exception is thrown.
			If case of reallocation, the storage is allocated using the container's allocator, which may throw exceptions on failure 
			(for the default allocator, bad_alloc is thrown if the allocation request does not succeed).

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ELEMENT ACCESS //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	operator[] // access element at index
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
			Returns a reference to the element at position n in the vector container.
			A similar member function, vector::at, has the same behavior as this operator function, except that vector::at is bound-checked 
			and signals if the requested position is out of range by throwing an out_of_range exception.
			Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.

	at // access element
		reference at (size_type n);
		const_reference at (size_type n) const;
			Returns a reference to the element at position n in the vector.
			The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not 
			(i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
				n: Position of an element in the container.
				If this is greater than, or equal to, the vector size, an exception of type out_of_range is thrown.
				Notice that the first element has a position of 0 (not 1).
				Member type size_type is an unsigned integral type.
	
	front // access first element
		reference front();
		const_reference front() const;
			Returns a reference to the first element in the vector.
			Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
			Calling this function on an empty container causes undefined behavior.
	
	back // access last element
		reference back();
		const_reference back() const;
			Returns a reference to the last element in the vector.
			Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
			Calling this function on an empty container causes undefined behavior.

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MODIFIERS //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	assign // assign vector content 
	push_back // add element at the end
	pop_back // delete last element
	insert // insert element
	erase // erase elements
	swap // swap content
	clear // clear content

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ALLOCATOR //
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	get_allocator // get allocator 


*/

#include "vector.hpp"

int		main( void )
{
	ft::vector<int> v(10, 10);
	v.print();
}