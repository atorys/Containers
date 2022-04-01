//
// Created by atory on 3/24/22.
//

#pragma once
#include "iostream"

#include "Iterator/reverse_iterator.hpp"
#include "Tree/tree.hpp"

namespace ft {

	template < class Key, class Type, class Compare = std::less<Key>,
	        class Alloc = std::allocator<ft::pair<const Key, Type> > >
	class	map {

		typedef	ft::RedBlackTree< RedBlackTreeTraits < ft::pair<const Key, Type>, Compare, Alloc> >	Container;

	private:
		Container	_c;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef ft::pair<const Key, Type>				valueType;
		typedef typename Alloc::template
		rebind<valueType>::other						allocType;
		typedef map <Key, Type, Compare, Alloc>			thisType;
		typedef Key										keyType;
		typedef Type									type;
		typedef Alloc									allocator;
		typedef typename Alloc::size_type				sizeType;
		typedef typename Alloc::difference_type			diffType;
//		typedef typename Alloc::value_type				valueType;
		typedef typename Alloc::pointer					ptr;
		typedef typename Alloc::reference				ref;
		typedef typename Alloc::const_pointer			const_ptr;
		typedef typename Alloc::const_reference			const_ref;

		typedef typename Container::iterator			iterator;
		typedef typename Container::const_iterator		const_iterator;

		//_2_Constructors_______________________________________________________________________________________________

		explicit	map(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): _c(comp, allocator) {}
		explicit	map(const Container& Cont):	_c(Cont) {}
		template < class Iter >
		map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& allocator = Alloc(),
			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): _c(comp, allocator)
		{
			if (first == last)
				return ;
			for (; first != last; ++first)
				_c.insert(*first);
		}
		explicit map(const thisType& other): _c(other._c) {}
		~map() { _c.clear(); }


		//_3_Capacity___________________________________________________________________________________________________

		sizeType				size()	const			{ return _c.size(); }
		sizeType				max_size()	const		{ return _c.max_size(); }
		bool 					empty() const			{ return _c.empty(); }
		Alloc					get_allocator() const	{ return _c.get_allocator(); }

		//_4_Element_access_____________________________________________________________________________________________

		iterator				begin()					{ return _c.begin(); }
		const_iterator			begin()	const			{ return _c.begin(); }
		iterator				end()					{ return _c.end(); }
		const_iterator			end() const				{ return _c.end(); }



	};
}
