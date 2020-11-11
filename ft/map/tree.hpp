/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:59:39 by imicah            #+#    #+#             */
/*   Updated: 2020/11/11 19:35:11 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINERS_TREE_HPP
# define FT_CONTAINERS_TREE_HPP

# include "ft.hpp"

template < class Key, class Value, class Compare, class Alloc>
class ft::tree
{
	friend class	ft::map<Key, Value>;
private:
	typedef				Key														key_type;
	typedef				Value													mapped_type;
	typedef				std::pair<const key_type, mapped_type>					value_type;
	typedef				std::size_t												size_type;

	enum color {
		_red	= true,
		_black	= false
	};

	typedef struct			_node_s {
		value_type*			_value;
		struct _node_s*		_left;
		struct _node_s*		_right;
		struct _node_s*		_parent;
		bool				_color;
	}						_node_t;

	typedef				_node_t											_node_type;
	typedef typename	Alloc::template rebind<_node_t>::other			_alloc_rebind_type;

	_node_t*				_root;
	_node_t*				_last_node;
	_node_t*				_first_node;

	size_type				_size;
	_alloc_rebind_type		_alloc_rebind;
	Alloc					_alloc;
	Compare					_compare;

	explicit tree(const Compare& comp = Compare(), const Alloc& alloc = Alloc())
																			: _size(0), _alloc(alloc), _compare(comp) {
		_empty_tree_init();
	}

	bool		_is_red(const _node_t* node) { return (node ? node->_color == _red : false); }

	bool		_is_black(const _node_t* node) { return (node ?  node->_color == _black : true); }

	void		_flip_color(_node_t* node) {
		node->_color = !node->_color;
		node->_right->_color = !node->_right->_color;
		node->_left->_color = !node->_left->_color;
	}

	_node_t*		_fix_up(_node_t* node) {
		if (_is_red(node->_right))
			node = _rotate_left(node);
		if (_is_red(node->_left) && _is_red(node->_left->_left))
			node = _rotate_right(node);
		if (_is_red(node->_right) && _is_red(node->_left))
			_flip_color(node);
		return (node);
	}

	_node_t*		_rotate_left(_node_t* node) {
		_node_t*		x = node->_right;

		if (x->_left) x->_left->_parent = node;
		x->_parent = node->_parent;
		node->_parent = x;

		node->_right = x->_left;
		x->_left = node;
		x->_color = node->_color;
		node->_color = _red;
		if (node == _root) _root = x;
		return (x);
	}

	_node_t*		_rotate_right(_node_t* node) {
		_node_t*		x = node->_left;

		if (x->_right) x->_right->_parent = node;
		x->_parent = node->_parent;
		node->_parent = x;

		node->_left = x->_right;
		x->_right = node;
		x->_color = node->_color;
		node->_color = _red;
		if (node == _root) _root = x;
		return (x);
	}

	_node_t*		_move_red_left(_node_t *node) {
		_flip_color(node);
		if (_is_red(node->_right->_left)) {
			node->_right = _rotate_right(node->_right);
			node = _rotate_left(node);
			_flip_color(node);
		}
		return (node);
	}

	_node_t*		_move_red_right(_node_t *node) {
		_flip_color(node);
		if (_is_red(node->_left->_left)) {
			node = _rotate_right(node);
			_flip_color(node);
		}
		return (node);
	}

	_node_t*		_create_new_node(const value_type& val, _node_t *parent) {
		_node_t*		x = _alloc_rebind.allocate(1);

		x->_value = _alloc.allocate(1);
		_alloc.construct(x->_value, val);

		x->_left = 0;
		x->_right = 0;

		if (_compare(val.first, _first_node->_parent->_value->first)) {
			x->_left = _first_node;
			_first_node->_parent = x;
		}
		else if (_compare(_last_node->_parent->_value->first, val.first)) {
			x->_right = _last_node;
			_last_node->_parent = x;
		}

		x->_parent = parent;
		x->_color = _red;
		return (x);
	}

	void		_empty_nodes_init() {
		_last_node->_right = _first_node;
		_last_node->_left = 0;
		_last_node->_parent = _first_node;

		_first_node->_right = 0;
		_first_node->_left = 0;
		_first_node->_parent = _last_node;

		_root = 0;
	}

	void		_empty_tree_init() {
		value_type	*value = _alloc.allocate(1);

		_alloc.construct(value, value_type());
		_last_node = _alloc_rebind.allocate(1);
		_first_node = _alloc_rebind.allocate(1);

		_last_node->_value = value;
		_first_node->_value = value;

		_last_node->_color = _black;
		_first_node->_color = _black;

		_empty_nodes_init();
	}

	void		_create_root_node(const value_type& val) {
		_root = _alloc_rebind.allocate(1);

		_root->_value = _alloc.allocate(1);
		_alloc.construct(_root->_value, val);

		_root->_left = _first_node;
		_root->_right = _last_node;
		_first_node->_parent = _root;
		_last_node->_parent = _root;
	}

	std::pair<_node_t*, bool>		_put(_node_t *node, const value_type& val) {
		std::pair<_node_t*, bool>	pair;
		bool		compare = _compare(val.first, node->_value->first);

		if (val.first == node->_value->first)
			return (std::make_pair(node, false));
		else if (_is_null_node(node->_left) && compare) {
			node->_left = _create_new_node(val, node);
			pair = std::make_pair(node, true);
		}
		else if (_is_null_node(node->_right) && !compare) {
			node->_right = _create_new_node(val, node);
			pair = std::make_pair(node, true);
		}
		else if (compare) {
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

	_node_t*		_delete_min(_node_t* node) {
		if (_is_null_node(node)) return (node);

		if (_is_null_node(node->_left))
			return (_destroy_node(node));

		else if (_is_black(node->_left) && _is_black(node->_left->_left))
			node = _move_red_left(node);

		node->_left = _delete_min(node->_left);
		return (_fix_up(node));
	}

	_node_t*		_delete_max(_node_t* node) {
		if (_is_null_node(node)) return (node);

		if (_is_red(node->_left))
			node = _rotate_right(node);

		if (_is_null_node(node->_right))
			return (_destroy_node(node));

		if (_is_black(node->_right) && _is_black(node->_right->_left))
			node = _move_red_right(node);

		node->_right = _delete_max(node->_right);
		return (_fix_up(node));
	}

	value_type*		_min(_node_t *node) {
		value_type*		val = _alloc.allocate(1);

		while (node->_left && node->_left != _first_node)
			node = node->_left;

		_alloc.construct(val, *node->_value);
		return (val);
	}

	bool			_is_null_node(_node_t* node) { return (node == 0 || node == _last_node || node == _first_node); }

	_node_t*		_delete(_node_t *node, const key_type &key) {
		if (_is_null_node(node)) return (node);

		bool	compare = _compare(node->_value->first, key);

		if (compare == 0 && node->_value->first != key) {
			if (_is_black(node->_left)&& _is_black(node->_left->_left))
				node = _move_red_left(node);
			node->_left = _delete(node->_left, key);
		}
		else {
			if (_is_red(node->_left))
				node = _rotate_right(node);
			if (node->_value->first == key && _is_null_node(node->_right))
				return (_destroy_node(node));
			if (_is_black(node->_right) && _is_black(node->_right->_left))
				node = _move_red_right(node);
			if (node->_value->first == key) {
				_alloc.destroy(node->_value);
				_alloc.deallocate(node->_value, 1);
				node->_value = _min(node->_right);
				node->_right = _delete_min(node->_right);
			}
			else
				node->_right = _delete(node->_right, key);
		}
		return (_fix_up(node));
	}

	_node_t*	_search(const key_type &key, _node_t *node) {
		_node_t*	result = node;

		while (result) {
			if (key == result->_value->first)
				break ;
			else if (_compare(key, result->_value->first))
				result = result->_left;
			else
				result = result->_right;
		}
		return (result);
	}

	_node_t*		_destroy_node(_node_t *node) {
		_node_t*		result = 0;
		if (node->_left == _first_node) {
			_first_node->_parent = node->_parent;
			result = _first_node;
		}
		else if (node->_right == _last_node) {
			_last_node->_parent = node->_parent;
			result = _last_node;
		}
		_alloc.destroy(node->_value);
		_alloc.deallocate(node->_value, 1);
		_alloc_rebind.deallocate(node, 1);
		_size--;
		return (result);
	}
};

#endif //FT_CONTAINERS_TREE_HPP
