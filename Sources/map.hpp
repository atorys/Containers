//
// Created by atory on 3/24/22.
//

#pragma once
#include "iostream"

#include "Iterator/reverse_iterator.hpp"
#include "Tree/tree.hpp"
#include "Iterator/tree_iterator.hpp"
#include "Utils/enable_if.hpp"
#include "Utils/is_integral.hpp"

namespace ft {

	template < class Key, class Type, class Compare = std::less<Key>,
	        class Alloc = std::allocator<ft::pair< const Key, Type> > >
	class	map: public ft::RedBlackTree< RedBlackTreeTraits < ft::pair< const Key, Type>, Compare, Alloc > > {

		typedef	ft::RedBlackTree< RedBlackTreeTraits < ft::pair< const Key, Type>, Compare, Alloc > >	Container;
		typedef map <Key, Type, Compare, Alloc>															Self;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef ft::pair< const Key, Type>				value_type;
//		typedef typename Alloc::template
//		rebind<value_type>::other						allocType;
		typedef Key										keyType;
		typedef Type									type;
		typedef Alloc									allocator;
		typedef typename Alloc::size_type				size_type;
		typedef typename Alloc::difference_type			difference_type;
//		typedef typename Alloc::value_type				valueType;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::const_reference			const_reference;

		typedef typename Container::iterator			iterator;
		typedef typename Container::const_iterator		const_iterator;

		//_2_Constructors_______________________________________________________________________________________________

		explicit	map(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): Container(comp, allocator) {}
		explicit	map(const Compare& comp): Container(comp, Alloc()) {}
					map(const Self& other): Container(other) {}

		template < class Iter >
		map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& allocator = Alloc(),
			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): Container(comp, allocator)
		{
			this->insert(first, last);
		}

		~map() { Container::clear(); }

	};
}
