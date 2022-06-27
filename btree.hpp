/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:45:38 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/24 07:00:39 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_HPP
#define BTREE_HPP

#include "map_iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template<class Key, class T>
	class subtree
	{
		public:
			ft::pair<const Key,T>	data;
			subtree*				L;
			subtree*				R;
			subtree*				P;
			size_t					H;
	};
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >, class subtree = subtree<const Key, T> >
	class btree
	{
		public :
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef Compare												key_compare;
			typedef ft::pair<const Key,T>								value_type;
			typedef std::allocator<ft::subtree<const Key,T> >			allocator_type_node;
			typedef std::allocator<ft::pair<const Key,T> >				allocator_type;
			typedef size_t												size_type;
			typedef int													difference_type;
			typedef ft::map_iterator<value_type, subtree>				iterator;
			typedef ft::map_iterator<const value_type, subtree>			const_iterator;
			typedef ft::reverse_map_iterator<value_type, subtree>		reverse_iterator;
			typedef ft::reverse_map_iterator<const value_type, subtree>	const_reverse_iterator;
		private:
			subtree *null_node;
			subtree *root;
			key_compare _keycmp;
			allocator_type _alloc;
			allocator_type_node _alloc_node;
		public:

			btree(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()) : _keycmp(cmp), _alloc(alloc)
			{
				null_node = alloc_node(value_type());
				null_node->P = NULL;
				null_node->R = NULL;
				null_node->L = NULL;
				null_node->H = 0;
				root = null_node;
			}

			~btree()
			{
				clear(begin(), end());
				_alloc_node.deallocate(null_node, 1);
			}

			btree& operator=(const btree& other)
			{
				clear(begin(), end());
				const_iterator it = other.begin(), ite = other.end();
				while (it != ite)
				{
					insert(ft::make_pair(it->first, it->second));
					++it;
				}
				return (*this);
			}

			ft::pair<iterator, bool> insert(value_type p)
			{
				if (root == null_node)
				{
					root = insert_node(root, p);
					return (ft::make_pair(iterator(root, null_node, root), true));
				}
				else
				{
					subtree *node = min_node(root);
					while (_keycmp(node->data.first, max_node(root)->data.first))
					{
						if (node->data.first == p.first)
							return(ft::make_pair(iterator(node, null_node, root), false));
						node = next(node);
					}
					if (max_node(root)->data.first == p.first)
						return(ft::make_pair(iterator(node, null_node, root), false));
					root = insert_node(root, p);
					node = min_node(root);
					while (node != null_node)
					{
						if (node->data.first == p.first)
							break ;
						node = next(node);
					}
					return (ft::make_pair(iterator(node, null_node, root), true));
				}
			}

			subtree * alloc_node(value_type i)
			{
				subtree *node = _alloc_node.allocate(1);
				_alloc.construct(&node->data, i);
				node->L = null_node;
				node->R = null_node;
				node->P = NULL;
				node->H = 1;
				return (node);
			}

			subtree *insert_node(subtree *node, ft::pair<const Key,T> pair)
			{
				if (root == null_node)
				{
					root = alloc_node(pair);
					return (root);
				}
				if (node == null_node)
				{
					node = alloc_node(pair);
					return (node);
				}
				if (_keycmp(pair.first, node->data.first))
				{
					node->L = insert_node(node->L, pair);
					node->L->P = node;
				}
				else if (_keycmp(node->data.first, pair.first))
				{
					node->R = insert_node(node->R, pair);
					node->R->P = node;
				}
				return (sort_tree(node));
			}

			subtree *delete_node(subtree *node, key_type type)
			{
				if (root == null_node)
					return (root);
				if (node == null_node)
					return (node);
				if (_keycmp(type, node->data.first))
					node->L = delete_node(node->L, type);
				else if (_keycmp(node->data.first, type))
					node->R = delete_node(node->R, type);
				else
				{
					subtree *tmp = null_node;
					if (node->L == null_node || node->R == null_node)
					{
						if (node->L != null_node)
							tmp = node->L;
						else
							tmp = node->R;
						if (tmp == null_node)
						{
							tmp = node;
							node = null_node;
						}
						else
						{
							if (node->L != null_node)
							{
								subtree *tmp2 = node->P;
								tmp = node;
								node = node->L;
								node->P = tmp2;
							}
							else if (node->R != null_node)
							{
								subtree *tmp2 = node->P;
								tmp = node;
								node = node->R;
								node->P = tmp2;
							}
						}
						if (!tmp->P && tmp->L == null_node && tmp->R == null_node)
						{
							_alloc.destroy(&tmp->data);
							_alloc_node.deallocate(tmp, 1);
							root = null_node;
						}
						else
						{
							if (root == tmp)
								root = node;
							_alloc.destroy(&tmp->data);
							_alloc_node.deallocate(tmp, 1);
						}
					}
					else if (node->L != null_node && node->R != null_node)
					{
						tmp = min_node(node->R);
						_alloc.destroy(&node->data);
						_alloc.construct(&node->data, tmp->data);
						node->R = delete_node(node->R, node->data.first);
					}
				}
				if (node == null_node)
					return (node);
				return (sort_tree(node));
			}

			int ft_sort(subtree *node)
			{
				if (node == null_node || !node)
					return (0);
				return (H(node->L) - H(node->R));
			}

			subtree *sort_tree(subtree * node)
			{
				node->H = H(node);
				int sort = ft_sort(node);
				if (sort > 1 && ft_sort(node->L) >= 0)
					node = R_rotate(node);
				else if (sort > 1 && ft_sort(node->L) < 0)
				{
					node->L = L_rotate(node->L);
					node = R_rotate(node);
				}
				else if (sort < -1 && ft_sort(node->R) <= 0)
					node = L_rotate(node);
				else if (sort < -1 && ft_sort(node->R) > 0)
				{
					node->R = R_rotate(node->R);
					node = L_rotate(node);
				}
				return (node);
			}

			size_t ft_highest(size_t i, size_t j)
			{
				if (_keycmp(j, i))
					return (i);
				return (j);
			}

			size_t H(subtree* node)
			{
				if (node == null_node)
					node->H = 0;
				else if (node->L == null_node && node->R == null_node)
					node->H = 1;
				else if (node->L == null_node && node->R != null_node)
					node->H = node->R->H + 1;
				else if (node->L != null_node && node->R == null_node)
					node->H = node->L->H + 1;
				else
					node->H = ft_highest(node->L->H, node->R->H) + 1;
				return (node->H);
			}

			subtree *L_rotate(subtree *node)
			{
				subtree *node2 = node->R;
				subtree *child_L = node2->L;
				subtree *tmp = node->P;
				node2->L = node;
				node->R = child_L;
				node->H = H(node);
				node2->H = H(node2);
				child_L->H = H(child_L);
				node->P = node2;
				node2->P = tmp;
				child_L->P = node;
				if (!node2->P)
					root = node2;
				return (node2);
			}

			subtree *R_rotate(subtree *node)
			{
				subtree *node2 = node->L;
				subtree *child_R = node2->R;
				subtree *tmp = node->P;
				node2->R = node;
				node->L = child_R;
				node->H = H(node);
				node2->H = H(node2);
				child_R->H = H(child_R);
				node->P = node2;
				node2->P = tmp;
				child_R->P = node;
				if (!node2->P)
					root = node2;
				return (node2);
			}

			const_iterator	ft_find(const key_type& k) const
			{
				if (root == null_node)
					return (end());
				subtree *max = max_node(root);
				subtree *min = min_node(root);
				while(min != max)
				{
					if (min->data.first == k)
						return(const_iterator(min, null_node, root));
					min = next(min);
				}
				if (max->data.first == k)
					return(const_iterator(max, null_node, root));
				else
					return (end());
			}

			iterator	ft_find(const key_type& k)
			{
				if (root == null_node)
					return (end());
				subtree *max = max_node(root);
				subtree *min = min_node(root);
				while(min != max)
				{
					if (min->data.first == k)
						return(iterator(min, null_node, root));
					min = next(min);
				}
				if (max->data.first == k)
					return(iterator(max, null_node, root));
				else
					return (end());
			}

			subtree* next(subtree * node) const
			{
				subtree *tmp;
				if (node->R == null_node)
				{
					tmp = node;
					while (tmp->P && tmp == tmp->P->R)
						tmp = tmp->P;
					tmp = tmp->P;
					return (tmp);
				}
				tmp = node->R;
				while (tmp->L != null_node)
					tmp = tmp->L;
				return (tmp);
			}

			void clear(iterator it, iterator ite)
			{
				while (it != ite)
				{
					subtree *max = max_node(root);
					subtree *min = min_node(root);
					subtree *tmp = null_node;
					while (min != max)
					{
						if (min->data.first == it->first)
							tmp = next(min);
						min = next(min);
					}
					if (max->data.first == it->first)
						tmp = null_node;
					
					delete_node(root, it->first);
					iterator tmp2(tmp, null_node, root);
					it = tmp2;
				}
			}

			size_type	count_nodes(const key_type& k)
			{
				const_iterator it = ft_find(k);
				if (ft_find(k) == end())
					return (0);
				return (1);
			}

			size_t erase (const key_type& i)
			{
				size_t ret  = 0;
				if (count_nodes(i))
					ret = 1;
				delete_node(root, i);
				return (ret);
			}

			subtree* min_node(subtree *node) const
			{
				if (node->L && node->L != null_node)
					return (min_node(node->L));
				return (node);
			}

			subtree* max_node(subtree *node) const
			{
				if (node->R && node->R != null_node)
					return (max_node(node->R));
				return (node);
			}

			subtree* search_node(subtree * node) const
			{
				subtree *tmp;
				if (node->R == null_node)
				{
					tmp = node;
					while (tmp->P && tmp == tmp->P->R)
						tmp = tmp->P;
					tmp = tmp->P;
					return (tmp);
				}
				tmp = node->R;
				while (tmp->L != null_node)
					tmp = tmp->L;
				return (tmp);
			}

			iterator begin()
			{
				if (root == null_node)
					return (iterator(root, null_node, root));
				subtree *tmp = min_node(root);
				return (iterator(tmp, null_node, root));
			}

			iterator end()
			{
				return (iterator(null_node, null_node, root));
			}

			const_iterator begin() const
			{
				if (root == null_node)
					return (const_iterator(root, null_node, root));
				subtree *tmp = min_node(root);
				return (const_iterator(tmp, null_node, root));
			}

			const_iterator end() const
			{
				return (const_iterator(null_node, null_node, root));
			}

			reverse_iterator rbegin()
			{
				if (root == null_node)
					return (reverse_iterator(root, null_node, root));
				subtree *tmp = max_node(root);
				return (reverse_iterator(tmp, null_node, root));
			}

			const_reverse_iterator rbegin() const
			{
				if (root == null_node)
					return (const_reverse_iterator(root, null_node, root));
				subtree *tmp = max_node(root);
				return (const_reverse_iterator(tmp, null_node, root));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(null_node, null_node, root));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(null_node, null_node, root));
			}

			size_t size() const
			{
				size_t size = 0;
				for (const_iterator it = begin() ; it != end() ; ++it)
					++size;
				return (size);
			}

			size_t count_nodes(subtree *node, size_t *i) const
			{
				if (node != null_node && node->L != null_node)
					count_nodes(root->L, i);
				if (node != null_node && node->R != null_node)
					count_nodes(node->R, i);
				if (node != null_node)
					(*i)++;
				return (*i);
			}

			T search(const Key &n)
			{
				subtree *tmp = root;
				while (tmp != null_node)
				{
					if (n < tmp->data.first)
					{
						if (tmp->L == null_node)
							return (0);
						tmp = tmp->L;
					}
					else if (n == tmp->data.first)
						return (tmp->data.second);
					else
					{
						if (tmp->R == null_node)
							return (0);
						else
							tmp = tmp->R;
					}
					return (tmp->data.second);
				}
				return (0);
			}

			void swap(btree &other)
			{
				subtree *tmp = other.null_node;
				other.null_node = null_node;
				null_node = tmp;
				subtree *tmp2 = other.root;
				other.root = root;
				root = tmp2;
				key_compare tmp3 = other._keycmp;
				other._keycmp = _keycmp;
				_keycmp = tmp3;
				allocator_type tmp4 = other._alloc;
				other._alloc = _alloc;
				_alloc = tmp4;
				allocator_type_node tmp5 = other._alloc_node;
				other._alloc_node = _alloc_node;
				_alloc_node = tmp5;
			}

			iterator upper_bound(const key_type& key)
			{
				if (root == null_node)
					return (end());
				iterator a = begin();
				for(; a != end(); ++a)
					if (_keycmp(key, a->first))
						return (a);
				return (a);
			}

			const_iterator upper_bound(const key_type& key) const
			{
				if (root == null_node)
					return (end());
				const_iterator a = begin();
				for(; a != end(); ++a)
					if (_keycmp(key, a->first))
						return (a);
				return (a);
			}

			iterator lower_bound(const key_type& key)
			{
				if (root == null_node)
					return (end());
				iterator a = begin();
				for(; a != end(); ++a)
					if (!_keycmp(a->first, key))
						return (a);
				return (a);
			}

			const_iterator lower_bound(const key_type& key) const
			{
				if (root == null_node)
					return (end());
				const_iterator a = begin();
				for(; a != end(); ++a)
					if (!_keycmp(a->first, key))
						return (a);
				return (a);
			}

			pair<iterator, iterator> equal_range(const key_type& key)
			{
				iterator it;
				iterator ite = upper_bound(key);
				if (lower_bound(key) != end())
					it = lower_bound(key);
				else
					it = upper_bound(key);
				return (ft::make_pair<iterator, iterator>(it, ite));
			}

			pair<const_iterator, const_iterator> equal_range(const key_type& key) const
			{
				const_iterator it;
				const_iterator ite = upper_bound(key);
				if (lower_bound(key) != end())
					it = lower_bound(key);
				else
					it = upper_bound(key);
				return (ft::make_pair<const_iterator, const_iterator>(it, ite));
			}

			iterator find(const key_type& key)
			{
				if (root == null_node)
					return (end());
				subtree *min = min_node(root);
				subtree *max = max_node(root);
				while(min != max)
				{
					if (min->data.first == key)
						return (iterator(min, null_node, root));
					min = next(min);
				}
				if (key == max->data.first)
					return (iterator(max, null_node, root));
				return end();
			}

			const_iterator find(const key_type& key) const
			{
				if (root == null_node)
					return (end());
				subtree *min = min_node(root);
				subtree *max = max_node(root);
				while(min != max)
				{
					if (min->data.first == key)
						return (const_iterator(min, null_node, root));
					min = next(min);
				}
				if (key == max->data.first)
					return (const_iterator(max, null_node, root));
				return end();
			}

			size_type count( const key_type& key ) const
			{
				const_iterator it = find(key);
				if (find(key) != end())
					return (1);
				return (0);
			}

			// FOR ME
			//void ft_print(subtree*node)
			//{
			//	if (node != null_node)
			//	{
			//		ft_print(node->L);
			//		ft_print(node->R);
			//		std::cout << node->data.second << std::endl;
			//	}
			//}
			//void ft_print()
			//{
			//	if (root != null_node)
			//	{
			//		ft_print(root->L);
			//		ft_print(root->R);
			//		std::cout << "root : " << root->data.second << std::endl;
			//	}
			//}
	};
}

#endif