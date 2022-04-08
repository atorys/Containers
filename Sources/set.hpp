//
// Created by Achiote Tory on 3/31/22.
//

#pragma once
#include "iostream"

#include "Iterator/reverse_iterator.hpp"
#include "Tree/tree.hpp"
#include "Iterator/tree_iterator.hpp"
#include "Utils/enable_if.hpp"
#include "Utils/is_integral.hpp"

namespace ft {

	template	< class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class	set : public ft::RedBlackTree< RedBlackTreeTraits < Key, Compare, Alloc > > {

		typedef	ft::RedBlackTree< RedBlackTreeTraits < Key, Compare, Alloc > >	Container;
		typedef set <Key, Compare, Alloc>										Self;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef Key												key_type;
		typedef Key												value_type;
		typedef Alloc											allocator_type;
		typedef Compare											key_compare;
		typedef Compare											value_compare;

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

		//_2_Constructors_______________________________________________________________________________________________

		explicit	set(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): Container(comp, allocator) {}
		explicit	set(const Compare& comp): Container(comp, Alloc()) {}
		set(const Self& other): Container(other) {}

		template < class Iter >
		set(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& allocator = Alloc(),
		typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): Container(comp, allocator)
		{
			for (; first != last; first++)
				this->insert(*first);
		}
		~set() { Container::clear(); }

		//_3_Observers__________________________________________________________________________________________________
		value_compare	value_comp() const	{ return (this->key_comp()); }

	};
}
