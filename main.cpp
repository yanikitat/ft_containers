/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:40:41 by imicah            #+#    #+#             */
/*   Updated: 2020/10/21 21:39:12 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "list.hpp"
#include <list>

TEMPLATE_TEST_CASE( "Default Constructors in list container", "[list]", int, char) {

	SECTION("CreateEmptyList_MatchWithOriginal") {
		ft::list<TestType>		ft_list;
		std::list<TestType>		list;

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
	}

	SECTION("CreateWithSize_MatchWithOriginal") {
		for (int i = 0; i < 10; i++) {
			ft::list<TestType>		ft_list(i);
			std::list<TestType>		list(i);

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			list.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("CreateWithSizeAndDefaultVal_MatchWithOriginal") {
		for (int i = 0; i < 10; i++) {
			ft::list<TestType>		ft_list(i, 'a' + i);
			std::list<TestType>		list(i,'a' + i);

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			REQUIRE(*list.begin() == *ft_list.begin());
			list.clear();
			// TODO added ft_list.clear()
		}
	}
}

TEMPLATE_TEST_CASE("Copy constructor in list container", "[list]", int, char) {

	SECTION("CreateEmptyList_MatchWithOriginal") {
		ft::list<TestType>		ft_list_for_copy;
		std::list<TestType>		list_for_copy;
		ft::list<TestType>		ft_list(ft_list_for_copy);
		std::list<TestType>		list(list_for_copy);

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
	}

	SECTION("CreateWithSize_MatchWithOriginal") {
		for (int i = 0; i < 10; i++) {
			ft::list<TestType>		ft_list_for_copy(i);
			std::list<TestType>		list_for_copy(i);
			ft::list<TestType>		ft_list(ft_list_for_copy);
			std::list<TestType>		list(list_for_copy);

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());

			list.clear();
			list_for_copy.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("CreateWithSizeAndDefaultVal_MatchWithOriginal") {
		for (int i = 0; i < 10; i++) {
			ft::list<TestType>		ft_list_for_copy(i, 'a' + i);
			std::list<TestType>		list_for_copy(i, 'a' + i);

			ft::list<TestType>		ft_list(ft_list_for_copy);
			std::list<TestType>		list(list_for_copy);

			*ft_list.begin();
			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			REQUIRE(*list.begin() == *ft_list.begin());
			list.clear();
			list_for_copy.clear();
			// TODO added ft_list.clear()
		}
	}
}

TEMPLATE_TEST_CASE("Assignation operator in list container", "[list]", int, char) {

	SECTION("CreateEmptyList_MatchWithOriginal") {
		ft::list<TestType>		ft_list_for_copy;
		std::list<TestType>		list_for_copy;
		ft::list<TestType>		ft_list = ft_list_for_copy;
		std::list<TestType>		list = list_for_copy;

		REQUIRE(list.empty() == ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
	}

	SECTION("CreateWithSize_MatchWithOriginal") {
		for (int i = 0; i < 20; i++) {
			ft::list<TestType>		ft_list_for_copy(i);
			std::list<TestType>		list_for_copy(i);

			ft::list<TestType>		ft_list = ft_list_for_copy;
			std::list<TestType>		list = list_for_copy;

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			list.clear();
			list_for_copy.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("CreateWithSizeAndDefaultVal_MatchWithOriginal") {
		for (int i = 0; i < 20; i++) {
			ft::list<TestType>		ft_list_for_copy(i, 'a' + i);
			std::list<TestType>		list_for_copy(i, 'a' + i);

			ft::list<TestType>		ft_list = ft_list_for_copy;
			std::list<TestType>		list = list_for_copy;

			*ft_list.begin();
			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			REQUIRE(*list.begin() == *ft_list.begin());
			list.clear();
			// TODO added ft_list.clear()
		}
	}
}

TEMPLATE_TEST_CASE("Constructor via iterators in list container", "[list]", int, char) {

	SECTION("CreateEmptyList_MatchWithOriginal") {
		ft::list<TestType>		ft_list_for_copy;
		std::list<TestType>		list_for_copy;
		ft::list<TestType>		ft_list(ft_list_for_copy.begin(), ft_list_for_copy.end());
		std::list<TestType>		list(list_for_copy.begin(), list_for_copy.end());

		REQUIRE(list.empty() != ft_list.empty());
		REQUIRE(list.size() == ft_list.size());
	}

	SECTION("CreateWithSize_MatchWithOriginal") {
		for (int i = 0; i < 20; i++) {
			ft::list<TestType>		ft_list_for_copy(i);
			std::list<TestType>		list_for_copy(i);

			ft::list<TestType>		ft_list(ft_list_for_copy.begin(), ft_list_for_copy.end());
			std::list<TestType>		list(list_for_copy.begin(), list_for_copy.end());

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			list.clear();
			list_for_copy.clear();
			// TODO added ft_list.clear()
		}
	}

	SECTION("CreateWithSizeAndDefaultVal_MatchWithOriginal") {
		for (int i = 0; i < 20; i++) {
			ft::list<TestType>		ft_list_for_copy(i, 'a' + i);
			std::list<TestType>		list_for_copy(i, 'a' + i);

			ft::list<TestType>		ft_list(ft_list_for_copy.begin(), ft_list_for_copy.end());
			std::list<TestType>		list(list_for_copy.begin(), list_for_copy.end());

			REQUIRE(list.empty() == ft_list.empty());
			REQUIRE(list.size() == ft_list.size());
			list.clear();
			list_for_copy.clear();
			// TODO added ft_list.clear()
		}
	}
}


//int 	main() {
//	ft::list<int>		ft_list_for_copy;
//	std::list<int>		list_for_copy;
//	ft::list<int>		ft_list(ft_list_for_copy);
//	std::list<int>		list(list_for_copy);
//
//}
