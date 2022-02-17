/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:49:21 by ablondel          #+#    #+#             */
/*   Updated: 2022/01/30 16:37:53 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>

int		main( void )
{
	int tab[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	easyfind<int*>(tab, 5);
	easyfind<int*>(tab, 15);
	int tab[10] = {1123, 21324, 2343, 4234, 545, 126, 34577, 96788, 9789, 1045};
	easyfind<int*>(tab, 34577);
	easyfind<int*>(tab, 1523);
	return 0;
}