/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:41:50 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/10 01:16:58 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	https://cdn.intra.42.fr/pdf/pdf/34895/fr.subject.pdf
**	https://www.cplusplus.com/reference/vector/vector/
**	https://anderberg.me/2016/07/04/c-custom-iterators/
**	https://stackoverflow.com/questions/21275190/c-custom-collection-reverse-iterator-with-similar-behaviour-to-stdvector-imp
**	https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/
*/

#include "vector.hpp"
#include "test.hpp"
#include <memory>
#include <iterator>
#include <vector>
#include <string>

int		main( void )
{
	ft::vector<int> fake(10);
	std::vector<int> real(10);

	if (fake == real)
		;
	return 0;
}
