//
// Created by atory on 3/24/22.
//

#pragma once
#include "iostream"
#include "Iterator/iterator.hpp"
#include "Iterator/iterator_category.hpp"
#include "Iterator/random_access_iterator.hpp"
#include "Iterator/reverse_iterator.hpp"
#include "Iterator/iterator_distance.hpp"

#include "tree.hpp"

namespace ft {

	template < class Key, class Type, class Comp = std::less<Key>,
	        class Alloc = std::allocator<ft::pair<const Key, Type> >,
			class Container = ft::tree<class Key, class Type, class Comp = std::less<Key>, Alloc > >
	class	map {
	private:
		Container	_c;

	public:
		typedef map <Key, Type, Comp, Alloc>			thisType;
		typedef ft::pair<const Key, Type>				valueType;
		typedef Key										keyType;
		typedef Type									type;
		typedef Alloc									allocator;
		typedef Comp									keyCompare;
		typedef typename Alloc::size_type				sizeType;
		typedef typename Alloc::difference_type			diffType;
//		typedef typename Alloc::value_type				valueType;
		typedef typename Alloc::pointer					ptr;
		typedef typename Alloc::reference				ref;
		typedef typename Alloc::const_pointer			const_ptr;
		typedef typename Alloc::const_reference			const_ref;


		// ??????
		typedef ft::random_access_iterator < RandIter <Type, diffType, ptr, ref> >				iterator;
		typedef ft::random_access_iterator < RandIter <Type, diffType, const_ptr, const_ref> >	const_iterator;
		typedef ft::reverse_iterator < iterator >												reverse_iterator;
		typedef ft::reverse_iterator < const_iterator >											const_reverse_iterator;



	};
}
