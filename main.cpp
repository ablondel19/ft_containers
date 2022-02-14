/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:50 by ablondel          #+#    #+#             */
/*   Updated: 2022/02/14 17:13:59 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
	
	// ITERATORS //
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


	
	// CAPACITY //
	size // return size of the vector
	max_size // return maximum size of the vector 
	resize // change size
	capacity // return size of allocated storage capacity 
	empty // test whether the vector is empty 
	reserve // request a change in capacity
	
	// ELEMENT ACCESS //
	operator[] // access element at index
	at // access element
	front // access first element
	back // access last element

	// MODIFIERS //
	assign // assign vector content 
	push_back // add element at the end
	pop_back // delete last element
	insert // insert element
	erase // erase elements
	swap // swap content
	clear // clear content

	// ALLOCATOR //
	get_allocator // get allocator 

/////////////////////////////



*/