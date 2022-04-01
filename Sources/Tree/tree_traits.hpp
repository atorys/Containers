//
// Created by Achiote Tory on 4/1/22.
//

#pragma once

#include "tree_node.hpp"
#include "../Utils/pair.hpp"

namespace ft {

	template < class Type, class Compare, class Alloc >
	struct	RedBlackTreeTraits {

		typedef Type								Data;
		typedef treeNode<Data>						Node;
		typedef Type								key_type;
		typedef Type								value_type;
		typedef Compare								key_compare;
		typedef Alloc								self_type_allocator;
		typedef typename Alloc::template
		rebind<Node >::other			allocator_for_node;


		typedef typename Alloc::size_type				sizeType;
		typedef typename Alloc::difference_type			diffType;
		typedef typename Alloc::pointer					ptr;
		typedef typename Alloc::reference				ref;
		typedef typename Alloc::const_pointer			const_ptr;
		typedef typename Alloc::const_reference			const_ref;

		typedef typename Alloc::template
		rebind<Node >::other::pointer			pointer;
		typedef typename Alloc::template
		rebind<Node >::other::const_pointer		const_pointer;
		typedef typename Alloc::template
		rebind<Node >::other::reference			reference;
		typedef typename Alloc::template
		rebind<Node >::other::const_reference	const_reference;

		key_type	GetKey(pointer X) const { return *(X->_data);}

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
		rebind<treeNode<Data> >::other		allocator_for_node;


		typedef typename Alloc::size_type				sizeType;
		typedef typename Alloc::difference_type			diffType;
		typedef typename Alloc::pointer					ptr;
		typedef typename Alloc::reference				ref;
		typedef typename Alloc::const_pointer			const_ptr;
		typedef typename Alloc::const_reference			const_ref;

		typedef typename Alloc::template
		rebind<Node >::other::pointer			pointer;
		typedef typename Alloc::template
		rebind<Node >::other::const_pointer		const_pointer;
		typedef typename Alloc::template
		rebind<Node >::other::reference			reference;
		typedef typename Alloc::template
		rebind<Node >::other::const_reference	const_reference;

		key_type	GetKey(pointer X) const { return X->_data->first;}

	};

}
