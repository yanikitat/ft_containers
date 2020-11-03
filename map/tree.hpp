/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:59:39 by imicah            #+#    #+#             */
/*   Updated: 2020/11/03 17:13:27 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TREE_HPP
# define FT_CONTAINERS_TREE_HPP

# include <iostream>
//# include "main.hpp"
//#include "map.hpp"

template < class Key, class Value, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,Value> > >
class map;

# define RED	true
# define BLACK	false

namespace ft {

	template < class Key, class Value, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,Value> > >
	class Tree
	{

		typedef				Key														key_type;
		typedef				Value													mapped_type;
		typedef				std::pair<const key_type, mapped_type>					value_type;
		typedef				std::size_t												size_type;

	public:
		struct		s_node {
			value_type					*_value;
			struct s_node				*_left;
			struct s_node				*_right;
			struct s_node				*_parent;
			bool						_color;
		};
		typedef				s_node											s_node;

		typedef typename	Alloc::template rebind<s_node>::other			alloc_rebind;

		s_node							*_root;
		s_node							*_last_node;
		s_node							*_first_node;
		s_node							*_end_node;

		size_type						_size;
		alloc_rebind					_alloc_rebind;
		Alloc							_alloc;
		Compare							_compare;

		explicit Tree(const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _size(0), _alloc(alloc), _compare(comp) {
			_empty_map_init();
		}
		friend class map<Key, Value>;

		template<class S>
		void		_swap(S &first, S &second) {
			S&	temp = S(first);

			first = temp;
			first = second;
		}

		bool		_is_red(const s_node* node) { return (node->_color == RED); }
		bool		_is_black(const s_node* node) { return (node->_color == BLACK); }

		void		_flip_color(s_node* node) {
			node->_color = !node->_color;
			node->_right->_color = !node->_right->_color;
			node->_left->_color = !node->_left->_color;
		}

		s_node*		_fix_up(s_node* node) {
			if (node->_right->_color == RED)
				node = _rotate_left(node);
			if (_is_red(node->_left) && _is_red(node->_left->_left))
				node = _rotate_right(node);
			if (_is_red(node->_right) && _is_red(node->_left))
				_flip_color(node);
			return (node);
		}

		s_node*		_rotate_left(s_node* node) {
			s_node*		x = node->_right;

			x->_left->_parent = node;
			x->_parent = node->_parent;
			node->_parent = x;

			node->_right = x->_left;
			x->_left = node;
			x->_color = node->_color;
			node->_color = RED;
			return (x);
		}

		s_node*		_rotate_right(s_node* node) {
			s_node*		x = node->_left;

			x->_right->_parent = node;
			x->_parent = node->_parent;
			node->_parent = x;

			node->_left = x->_right;
			x->_right = node;
			x->_color = node->_color;
			node->_color = RED;
			return (x);
		}

		s_node*		_move_red_left(s_node *node) {
			_flip_color(node);
			if (_is_red(node->_right->_left)) {
				node->_right = _rotate_right(node->_right);
				node = _rotate_left(node);
				_flip_color(node);
			}
			return (node);
		}

		s_node*		_move_red_right(s_node *node) {
			_flip_color(node);
			if (_is_red(node->_left->_left)) {
				node = _rotate_right(node);
				_flip_color(node);
			}
			return (node);
		}

		s_node*		_create_new_node(const value_type& val, s_node *parent) {
			s_node*		x = _alloc_rebind.allocate(1);

			x->_value = _alloc.allocate(1);
			_alloc.construct(x->_value, val);

			if (_compare(val.first, _first_node->_parent->_value->first)) {
				x->_left = _first_node;
				_first_node->_parent = x;
			}
			else
				x->_left = _end_node;

			if (_compare(_last_node->_parent->_value->first, val.first)) {
				x->_right = _last_node;
				_last_node->_parent = x;
			}
			else
				x->_right = _end_node;

			x->_parent = parent;
			x->_color = RED;
			return (x);
		}

		void		_create_end_node() {
			value_type	*value = _alloc.allocate(1);

			_alloc.construct(value, value_type());
			_last_node = _alloc_rebind.allocate(1);
			_first_node = _alloc_rebind.allocate(1);
			_end_node = _alloc_rebind.allocate(1);

			_last_node->_value = value;
			_first_node->_value = value;
			_end_node->_value = value;

			_last_node->_color = BLACK;
			_first_node->_color = BLACK;
			_end_node->_color = BLACK;

			_end_node->_right = 0;
			_end_node->_left = 0;
			_end_node->_parent = _end_node;

			_last_node->_right = 0;
			_last_node->_left = 0;
			_last_node->_parent = _end_node;

			_first_node->_right = 0;
			_first_node->_left = 0;
			_first_node->_parent = _end_node;
		}

		void		_empty_map_init() {
			_create_end_node();
			_root = _end_node;
		}

		std::pair<s_node*, bool>		_put(s_node *node, const value_type& val) {
			std::pair<s_node*, bool>	pair;

			if (val.first == node->_value->first)
				return (std::make_pair(node, false));

			if ((node->_left == _first_node || node->_left == _end_node) && _compare(val.first, node->_value->first)) {
				node->_left = _create_new_node(val, node);
				pair = std::make_pair(node, true);
			}
			else if ((node->_right == _last_node || node->_right == _end_node) && _compare(node->_value->first, val.first)) {
				node->_right = _create_new_node(val, node);
				pair = std::make_pair(node, true);
			}
			else if (_compare(val.first, node->_value->first)) {
				pair = _put(node->_left, val);
				node->_left = pair.first;
			}
			else {
				pair = _put(node->_right, val);
				node->_right = pair.first;
			}

			node = _fix_up(node);
			return (std::make_pair(node, pair.second));
		}

		s_node		*_delete_min(s_node *node) {
			if (node->_left == _last_node && node->_right == _last_node) {
				_destroy_node(node);
				return (_last_node);
			}
			if (_is_black(node->_left) && _is_black(node->_left->_left))
				_move_red_left(node);
			node->_left = _delete_min(node->_left);
			return (_fix_up(node));
		}

		value_type	*_min(s_node *node) {
			while (node->_left != _first_node)
				node = node->_left;
			return (node->_value);
		}

		s_node		*_delete(s_node *node, const key_type &key) {
			int		compare = _compare(node->_value->first, key);

			if (!compare && node->_value->first != key) {
				if (_is_black(node->_left)&& _is_black(node->_left->_left))
					_move_red_left(node);
				node->_left = _delete(node->_left, key);
			}
			else {
				if (_is_red(node->_left))
					node = _rotate_right(node);
				if (node->_value->first == key && node->_right == _last_node) {
					_destroy_node(node);
					return (_last_node);
				}
				if (_is_black(node->_right) && _is_black(node->_right->_left))
					node = _move_red_right(node);
				if (node->_value->first == key) {
					node->_value = _min(node->_right);
					node->_right = _delete_min(node->_right);
				}
				else
					node->_right = _delete(node->_right, key);
			}
			return _fix_up(node);
		}

		s_node		*_delete(s_node *node) {
			if (_is_red(node->_left))
				node = _rotate_right(node);
			if (node->_right == _last_node) {
				_destroy_node(node);
				return (_last_node);
			}
			if (_is_black(node->_right) && _is_black(node->_right->_left))
				node = _move_red_right(node);
			node->_value = _min(node->_right);
			node->_right = _delete_min(node->_right);
			return _fix_up(node);
		}

		s_node		*_search(const key_type &key, s_node *node) {
			s_node	*temp_node = node;

			while (temp_node != _last_node) {
				if (key == temp_node->_value->first)
					break ;
				else if (_compare(key, temp_node->_value->first))
					temp_node = temp_node->_left;
				else
					temp_node = temp_node->_right;
			}
			return (temp_node);
		}

		void		_destroy_node(s_node *node) {
			_alloc.deallocate(node->_value, 1);
			_alloc_rebind.deallocate(node, 1);
			_size--;
		}

		s_node		*_get_min_node() {
			_first_node = _root;

			while (_first_node != _last_node && _first_node->_left != _last_node)
				_first_node = _first_node->_left;
			_first_node->_parent = _first_node;
			return (_first_node);
		}

		s_node		*_get_max_node() {
			_last_node = _root;

			while (_last_node != _last_node && _last_node->_right != _last_node)
				_last_node = _last_node->_right;
			_last_node->_parent = _last_node;
			return (_last_node);
		}

	};
}

#endif //FT_CONTAINERS_TREE_HPP
