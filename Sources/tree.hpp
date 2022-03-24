//
// Created by atory on 3/24/22.
//

#pragma once

namespace ft {

	struct tree_traits {
		typedef	T1	keyType;
	};

	template < class Tr >
	class	treeNode : public Tr {
	protected:
		typedef typename Tr::allocator_type			allocator;
		typedef	typename Tr::key_compare			keyCompare;
		typedef typename Tr::value_type				valueType;
		typedef typename allocator::template rebind	valueType;
	};
}
