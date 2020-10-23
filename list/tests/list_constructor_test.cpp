/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_constructor_test.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:40:41 by imicah            #+#    #+#             */
/*   Updated: 2020/10/23 11:54:40 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "list.hpp"
#include "catch.hpp"

TEMPLATE_TEST_CASE_SIG( "Default Constructors in list container", "[list] [constructor]",
		((typename T, int V), T, V), (int, 10), (char, 20)) {

	SECTION("CreateEmptyList_MatchWithOriginal") {
		ft::list<T>		ft_list;
		std::list<T>	list;

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
	}

	SECTION("CreateWithSize_MatchWithOriginal") {
		for (int i = 0; i < V; i++) {
			ft::list<T>		ft_list(i);
			std::list<T>	list(i);

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());

			list.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("CreateWithSizeAndDefaultVal_MatchWithOriginal") {
		for (int i = 0; i < V; i++) {
			ft::list<T>		ft_list(i, 'a' + i);
			std::list<T>	list(i,'a' + i);

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());

			list.clear();
			// TODO added ft_list.clear()
		}
	}
}

TEMPLATE_TEST_CASE_SIG("Copy constructor in list container", "[list] [constructor]",
											((typename T, int V), T, V), (int, 10), (char, 20)) {
	ft::list<T>		ft_list_for_copy;
	std::list<T>	list_for_copy;

	SECTION("EmptyList_MatchWithOriginal") {
		ft::list<T>		ft_list(ft_list_for_copy);
		std::list<T>	list(list_for_copy);

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
		REQUIRE(list.front() == ft_list.front());
		REQUIRE(list.back() == list.back());
	}

	SECTION("WithSize_MatchWithOriginal") {
		for (int i = 0; i < V; i++) {
			ft::list<T>		ft_list(ft_list_for_copy);
			std::list<T>	list(list_for_copy);

			REQUIRE(list.size() == ft_list.size());
			REQUIRE(list.back() == list.back());

			ft_list_for_copy.push_back(i);
			list_for_copy.push_back(i);
			list.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("WithSizeAndDefaultVal_MatchWithOriginal") {
		ft::list<T>		ft_list_for_copy(0, 'a');
		std::list<T>	list_for_copy(0, 'a');

		for (int i = 0; i < V; i++) {

			ft::list<T>		ft_list(ft_list_for_copy);
			std::list<T>		list(list_for_copy);

			REQUIRE(list.size() == ft_list.size());
			REQUIRE(list.back() == list.back());

			ft_list_for_copy.push_back('a' + i);
			list_for_copy.push_back('a' + i);
			list.clear();
			// TODO added ft_list.clear()
		}
	}
}

TEMPLATE_TEST_CASE_SIG("Assignation operator in list container", "[list] [constructor]",
											   ((typename T, int V), T, V), (int, 10), (char, 20)) {
	ft::list<T>		ft_list_for_copy;
	std::list<T>	list_for_copy;

	SECTION("EmptyList_MatchWithOriginal") {
		ft::list<T>		ft_list = ft_list_for_copy;
		std::list<T>	list = list_for_copy;

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
		REQUIRE(list.front() == ft_list.front());
		REQUIRE(list.back() == list.back());
	}

	SECTION("WithSize_MatchWithOriginal") {
		for (int i = 0; i < V; i++) {
			ft::list<T>		ft_list = ft_list_for_copy;
			std::list<T>	list = list_for_copy;

			REQUIRE(list.size() == ft_list.size());
			REQUIRE(list.back() == list.back());

			list_for_copy.push_back(i);
			ft_list_for_copy.push_back(i);
			list.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("WithSizeAndDefaultVal_MatchWithOriginal") {
		ft::list<T>		ft_list_for_copy(0, 'a');
		std::list<T>	list_for_copy(0, 'a');

		for (int i = 0; i < V; i++) {
			ft::list<T>		ft_list = ft_list_for_copy;
			std::list<T>	list = list_for_copy;

			REQUIRE(list.size() == ft_list.size());
			REQUIRE(list.back() == list.back());

			list_for_copy.push_back(i);
			ft_list_for_copy.push_back(i);
			list.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("AssignationWithDifferentSize") {
		ft::list<T>		ft_list_for_copy(12);
		std::list<T>	list_for_copy(12);

		SECTION("AssignationWithLowerSize") {
			ft::list<T>		ft_list(6);
			std::list<T>	list(6);

			ft_list = ft_list_for_copy;
			list = list_for_copy;

			REQUIRE(list.size() == ft_list.size());
			REQUIRE(list.front() == ft_list.front());
			REQUIRE(list.back() == list.back());
		}

		SECTION("AssignationWithGreaterSize") {
			ft::list<T>		ft_list(24);
			std::list<T>	list(24);

			ft_list = ft_list_for_copy;
			list = list_for_copy;

			REQUIRE(list.size() == ft_list.size());
			REQUIRE(list.front() == ft_list.front());
			REQUIRE(list.back() == list.back());
		}
	}
}

TEMPLATE_TEST_CASE_SIG("Constructor via iterators in list container", "[list] [constructor]",
											   ((typename T, int V), T, V), (int, 10), (char, 20)) {

	ft::list<T>		ft_list_for_copy;
	std::list<T>	list_for_copy;

	SECTION("EmptyList_MatchWithOriginal") {
		ft::list<T>		ft_list(ft_list_for_copy.begin(), ft_list_for_copy.end());
		std::list<T>	list(list_for_copy.begin(), list_for_copy.end());

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
	}

	SECTION("WithSize_MatchWithOriginal") {
		for (int i = 0; i < V; i++) {

			ft::list<T>		ft_list(ft_list_for_copy.begin(), ft_list_for_copy.end());
			std::list<T>	list(list_for_copy.begin(), list_for_copy.end());

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());

			ft_list_for_copy.push_back(i);
			list_for_copy.push_back(i);
			list.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("WithSizeAndDefaultVal_MatchWithOriginal") {
		ft::list<T>		ft_list_for_copy(0, 'a');
		std::list<T>	list_for_copy(0, 'a');

		for (int i = 0; i < V; i++) {

			ft::list<T>		ft_list(ft_list_for_copy.begin(), ft_list_for_copy.end());
			std::list<T>	list(list_for_copy.begin(), list_for_copy.end());

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());

			ft_list_for_copy.push_back(i);
			list_for_copy.push_back(i);
			list.clear();
			// TODO added ft_list.clear()
		}
	}
}
