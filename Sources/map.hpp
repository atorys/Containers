//
// Created by atory on 3/24/22.
//

#pragma once
#include <iostream>

#include "Tree/tree.hpp"
#include "Iterator/reverse_iterator.hpp"
#include "Iterator/tree_iterator.hpp"
#include "Utils/utility.hpp"

namespace ft {

	template < class Key, class Type, class Compare = std::less<Key>,
	        class Alloc = std::allocator<ft::pair< const Key, Type> > >
	class	map: public ft::RedBlackTree< RedBlackTreeTraits < ft::pair< const Key, Type>, Compare, Alloc > > {

		typedef	ft::RedBlackTree< RedBlackTreeTraits < ft::pair< const Key, Type>, Compare, Alloc > >	Container;
		typedef map <Key, Type, Compare, Alloc>															Self;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef ft::pair< const Key, Type>						value_type;
		typedef Key												key_type;
		typedef Type											mapped_type;
		typedef Alloc											allocator_type;
		typedef Compare											key_compare;
		typedef typename Alloc::size_type						size_type;
		typedef typename Alloc::difference_type					difference_type;
		typedef typename Alloc::pointer							pointer;
		typedef typename Alloc::reference						reference;
		typedef typename Alloc::const_pointer					const_pointer;
		typedef typename Alloc::const_reference					const_reference;

		typedef typename Container::iterator					iterator;
		typedef typename Container::const_iterator				const_iterator;
		typedef typename Container::reverse_iterator			reverse_iterator;
		typedef typename Container::const_reverse_iterator		const_reverse_iterator;

		//_1_2_Member_Classes___________________________________________________________________________________________

		class value_compare : public std::binary_function <value_type, value_type, bool> {
			friend class map;
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				bool operator() (const value_type& X, const value_type& Y) const { return comp(X.first, Y.first); }
		};

		//_2_Constructors_______________________________________________________________________________________________

		explicit	map(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): Container(comp, allocator) {}
//		explicit	map(const Compare& comp): Container(comp, Alloc()) {}
					map(const Self& other): Container(other) {}

		template < class Iter >
		map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& allocator = Alloc(),
			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): Container(comp, allocator)
		{
			this->insert(first, last);
		}

		~map() { Container::clear(); }

		//_3_Observers__________________________________________________________________________________________________
		value_compare	value_comp() const	{ return (value_compare(this->key_comp())); }

	};
}
