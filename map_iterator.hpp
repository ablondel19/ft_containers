/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 08:19:24 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/26 21:03:15 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "btree.hpp"
#include "enable_if.hpp"
#include "pair.hpp"

namespace ft
{
	template<typename value_type, typename subtree>
	class reverse_map_iterator;

	template<typename value_type, typename subtree>
	class map_iterator
	{
		public:
			typedef std::random_access_iterator_tag			iterator_category;
			typedef value_type&								reference;
			typedef value_type*								pointer;
			typedef	typename value_type::first_type			key_type;
			typedef map_iterator<value_type, subtree>		iterator_type;
			typedef	typename value_type::second_type		mapped_type;
			typedef size_t									size_type;
			typedef int										difference_type;
		
		private:
			subtree *_root;
			subtree *_null_node;
			subtree *_current_node;
		
		public:
			map_iterator(): _root(NULL), _null_node(NULL), _current_node(NULL) {}
			map_iterator(subtree *other_node, subtree *n, subtree *r): _root(r), _null_node(n), _current_node(other_node) {}
			map_iterator(const map_iterator<value_type, subtree> & obj): _root(obj._root), _null_node(obj._null_node), _current_node(obj._current_node) {}
			map_iterator(const reverse_map_iterator<value_type, subtree>& it, int) : _root(it.get_root_node()), _null_node(it.get_null_node()), _current_node(it.get_current_node()) {}
			~map_iterator() {}
			
			subtree *successor(subtree *node)
			{
				subtree *tmp;
				if (node->R == _null_node)
				{
					tmp = node;
					while (tmp->P && tmp == tmp->P->R)
						tmp = tmp->P;
					tmp = tmp->P;
					return (tmp);
				}
				tmp = node->R;
				while (tmp->L != _null_node)
					tmp = tmp->L;
				return (tmp);
			}
			
			subtree *predecessor(subtree *node)
			{
				subtree *tmp;
				if (node->L == _null_node || !node->L)
				{
					tmp = node;
					while (tmp->P && tmp == tmp->P->L)
						tmp = tmp->P;
					tmp = tmp ->P;
					return (tmp);
				}
				tmp = node->L;
				while (tmp->R != _null_node)
					tmp = tmp->R;
				return (tmp);
			}
			
			subtree *max_node(subtree *node) const
			{
				if (node == _null_node)
					return (node);
				if (node->R && node->R != _null_node)
					return (max_node(node->R));
				return (node);
			}
			
			subtree *min_node(subtree *node) const
			{
				if (node->L && node->L != _null_node)
					return (min_node(node->L));
				return (node);
			}
			
			subtree *get_root_node() const
			{
				return (_root);
			}
			
			subtree *get_current_node() const
			{
				return (_current_node);
			}
			
			subtree *get_null_node() const
			{
				return (_null_node);
			}
			
			map_iterator &operator=(const map_iterator &obj)
			{
				_null_node = obj._null_node;
				_root = obj._root;
				_current_node = obj._current_node;
				return (*this);
			}
			
			reference operator*() const
			{
				return (_current_node->data);
			}
			
			pointer operator->() const
			{
				return (&(_current_node)->data);
			}
			
			operator	map_iterator<value_type const, subtree>() const
			{
				return (map_iterator<value_type const, subtree>(_current_node, _null_node, _root));
			}
			
			map_iterator& operator++()
			{
				if(_current_node == _null_node)
					_current_node = min_node(_root);
				else if (_current_node == max_node(_root))
					_current_node = _null_node;
				else
					_current_node = successor(_current_node);
				return (*this);
			}
			
			map_iterator operator++(int)
			{
				map_iterator<value_type, subtree> tmp(*this);
				this->operator++();
				return (tmp);
			}
			
			map_iterator& operator--()
			{
				if (_current_node == _null_node)
					_current_node = max_node(_root);
				else
					_current_node = predecessor(_current_node);
				return (*this);
			}
			
			map_iterator operator--(int)
			{
				map_iterator<value_type, subtree> tmp(*this);
				this->operator--();
				return (tmp);
			}
			
			bool operator==(const map_iterator &obj) const
			{
				return (_current_node == obj._current_node);
			}

			bool operator!=(const map_iterator &obj) const
			{
				return (_current_node != obj._current_node);
			}

	};
}

#endif