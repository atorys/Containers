//
// Created by Achiote Tory on 4/1/22.
//

#pragma once

#include "tree_node.hpp"
#include "../Utils/pair.hpp"

namespace ft {

	/**
	 * Template class Tree Traits
	 *
	 * Нужен для построения корректного узла дерева.
	 *
	 * В зависимости от приходящих значений
	 * может поддерживать 2 вида узла дерева:
	 * 										 	1) treeNode < Type >					(set)
	 * 										 	2) treeNode <  ft::pair< Key, Type> >	(map)
	 *
	 *
	 * Определяет тип входящей ноды и аллокатор для нее, а так же получает указатели и ссылки на саму ноду
	 * и внутренние данные, определяет тип узла дерева как Node.
	 * Для 2 видов узлов определена функция GetKey(), которая в зависимости
	 * от типа возвращает ключ ноды:
	 * 											1) treeNode < Type > 					вернет Type
	 * 											2) treeNode <  ft::pair< Key, Type> >	вернет Key
	 *
	 */

	template < class Type, class Compare = std::less<Type>, class Alloc = std::allocator<Type> >
	struct	RedBlackTreeTraits {

		typedef Type								Data;
		typedef treeNode<Data>						Node;
		typedef Type								key_type;
		typedef Type								value_type;
		typedef Compare								key_compare;
		typedef Alloc								self_type_allocator;
		typedef typename Alloc::template
		rebind<Node >::other						allocator_for_node;
		typedef typename Alloc::template
		rebind<treeNode<Data>* >::other				allocator_for_node_ptr;


		typedef typename Alloc::size_type				size_type;
		typedef typename Alloc::difference_type			difference_type;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::const_reference			const_reference;

		typedef typename Alloc::template
		rebind<Node >::other::pointer			nodePtr;
		typedef typename Alloc::template
		rebind<Node >::other::const_pointer		const_nodePtr;
		typedef typename Alloc::template
		rebind<Node >::other::reference			nodeRef;
		typedef typename Alloc::template
		rebind<Node >::other::const_reference	const_nodeRef;

		static key_type&			GetKey(nodePtr X)			{ return *(X->_data); }
		static const key_type&		GetKey(Data const& X)		{ return (X); }
		static value_type&			GetValue(nodePtr X) 		{ return *(X->_data); }
		static const value_type&	GetValue(Data const& X)		{ return (X); }

	};

	template < class Key, class Type, class Compare, class Alloc >
	struct	RedBlackTreeTraits < ft::pair< Key, Type>, Compare, Alloc > {

		typedef ft::pair<const Key, Type>			Data;
		typedef treeNode<Data>						Node;
		typedef Key									key_type;
		typedef Type								value_type;
		typedef Compare								key_compare;
		typedef Alloc								self_type_allocator;
		typedef typename Alloc::template
		rebind<treeNode<Data> >::other				allocator_for_node;
		typedef typename Alloc::template
		rebind<treeNode<Data>* >::other				allocator_for_node_ptr;


		typedef Data*		pointer;
		typedef Data&		reference;


		typedef typename Alloc::size_type				size_type;
		typedef typename Alloc::difference_type			difference_type;
//		typedef typename Alloc::pointer					pointer;
//		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::const_reference			const_reference;

		typedef typename Alloc::template
		rebind<Node >::other::pointer			nodePtr;
		typedef typename Alloc::template
		rebind<Node >::other::const_pointer		const_nodePtr;
		typedef typename Alloc::template
		rebind<Node >::other::reference			nodeRef;
		typedef typename Alloc::template
		rebind<Node >::other::const_reference	const_nodeRef;

		static key_type&			GetKey(nodePtr X)		{ return X->_data->first; }
		static const key_type&		GetKey(Data const& X) 	{ return X.first; }
		static value_type&			GetValue(nodePtr X) 	{ return X->_data->second; }
		static const value_type&	GetValue(Data const& X) { return X.second; }

	};

}
