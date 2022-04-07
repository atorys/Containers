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

	template < class Key, class Compare = std::less<Key>,
			class Alloc = std::allocator<Key> >
	class set : public ft::RedBlackTree< RedBlackTreeTraits < Key, Compare, Alloc > > {

		typedef	ft::RedBlackTree< RedBlackTreeTraits < Key, Compare, Alloc > >	Container;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef Key										keyType;
		typedef Key										value_type;
		typedef typename Alloc::template
		rebind<value_type>::other						allocType;
		typedef typename Alloc::template
		rebind<value_type>::other::pointer				allocPtr;
		typedef set <Key, Compare, Alloc>				Self;
		typedef Key										type;
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

	};
}
