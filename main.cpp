/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:40:41 by imicah            #+#    #+#             */
/*   Updated: 2020/10/21 13:48:38 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "list/list.hpp"

int main() {

	ft::list<char>		list(3, 'q');
//	ft::list<char>::iterator	begin = list.begin();
//	ft::list<char>::iterator	end = list.end();
//
	ft::list<char>		list_2(list);

	return (0);
}
