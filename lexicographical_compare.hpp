/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:01:35 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/17 19:16:22 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
	template < class InputIterator1, class InputIterator2 >
	bool	equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
				return 0;
			++first1;
			++first2;
		}
		return 1;
	}
	
	template < class InputIterator1, class InputIterator2 >
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return 0;
			else if (*first1 < *first2)
				return 1;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	
	template < class InputIterator1, class InputIterator2, class Compare >
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2 == last2 || !comp(*first2, *first1))
				return 0;
			else if (!comp(*first2, *first1))
				return 1;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif // !LEXICOGRAPHICAL_COMPARE_HPP