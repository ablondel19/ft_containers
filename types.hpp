/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:34:59 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/11 02:57:15 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_HPP
#define TYPES_HPP
#include <type_traits>

namespace ft
{
	/* ENABLE IF CONDITION IS MET */
		
		//It is defined with a behavior equivalent to :
			//	template<bool Cond, class T = void> struct enable_if {};
			//	template<class T> struct enable_if<true, T> { typedef T type; };

		//The type T is enabled as member type enable_if::type if Cond is true
		//Otherwise, enable_if::type is not defined.
		
		//This is useful to hide the signatures on compile time when a particular
		//condition is not met, since in this case, the member enable_if::type
		//will not be defined and attempting to compile using it should fail. 
	
	typedef std::integral_constant < bool, true > true_type;
	typedef std::integral_constant < bool, false > false_type;
	
	template < bool Cond, typename T = void >
	struct enable_if {};

	template < typename T >
	struct enable_if <true, T> { typedef T type; };
	
	template < class T >
	struct is_integral : public false_type {};
	
	template < class T >
	struct is_integral < const T > : public is_integral < T > {};
	
	template < class T >
	struct is_integral < volatile const T > : public is_integral < T > {};
		
	template < class T >
	struct is_integral < volatile T > : public is_integral < T > {};

	template <  >
	struct is_integral < unsigned char > : public true_type {};

	template <  >
	struct is_integral < unsigned short > : public true_type {};
	
	template <  >
	struct is_integral < unsigned int > : public true_type {};

	template <  >
	struct is_integral < unsigned long > : public true_type {};

	template <  >
	struct is_integral < unsigned long long > : public true_type {};

	template <  >
	struct is_integral < signed char > : public true_type {};

	template <  >
	struct is_integral < short > : public true_type {};

	template <  >
	struct is_integral < int > : public true_type {};

	template <  >
	struct is_integral < long > : public true_type {};

	template <  >
	struct is_integral < char > : public true_type {};

	template <  >
	struct is_integral < bool > : public true_type {};

	template <  >
	struct is_integral < char16_t > : public true_type {};

	template <  >
	struct is_integral < char32_t > : public true_type {};

	template <  >
	struct is_integral < wchar_t > : public true_type {};

}

#endif // !TYPES_HPP