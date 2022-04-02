//
// Created by Achiote Tory on 3/31/22.
//

#pragma once
#include "iostream"

#include "Iterator/reverse_iterator.hpp"
#include "Tree/tree.hpp"
#include "Utils/enable_if.hpp"
#include "Utils/is_integral.hpp"

namespace ft {

	template < class Key, class Compare = std::less<Key>,
			class Alloc = std::allocator<Key> >
	class set {

		typedef	ft::RedBlackTree< RedBlackTreeTraits < Key, Compare, Alloc > >	Container;

	private:
		Container	_c;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef Key										keyType;
		typedef Key										valueType;
		typedef typename Alloc::template
		rebind<valueType>::other						allocType;
		typedef typename Alloc::template
		rebind<valueType>::other::pointer				allocPtr;
		typedef set <Key, Compare, Alloc>				Self;
		typedef Key										type;
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

		explicit	set(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): _c(comp, allocator) {}
		template < class Iter >
		set(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& A = Alloc(),
		typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): _c(comp, A)
		{
				if (first == last)
					return ;
				for (; first != last; ++first)
					_c.insert(*first);
		}
		explicit set(const Self& other): _c(other._c) {}
		~set() { clear(); }


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


		void	clear()	{ _c.clear(); }
		void	insert(const valueType& X) { _c.insert(X); }

		template < class Iter >
		void	insert(Iter first, Iter last,
					   typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr)
		{
			if (first == last)
				return ;
			for (; first != last; ++first)
				_c.insert(*first);
		}

	};
}
