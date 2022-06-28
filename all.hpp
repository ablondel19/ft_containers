/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 08:05:19 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/28 08:16:14 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_HPP
#define ALL_HPP
#include <exception>
#include <memory>
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"

#ifdef VECTOR_HPP
	#include "iterator.hpp"
	#include "reverse_iterator.hpp"
#endif // VECTOR_HPP

#ifdef MAP_HPP
	#include "iterator.hpp"
	#include "pair.hpp"
	#include "btree.hpp"
	#include "map_iterator.hpp"
	#include "map_reverse_iterator.hpp"
#endif // MAP_HPP


#endif // !ALL_HPP