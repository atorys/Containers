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

//	private:
//		Container	_c;

	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef ft::pair< const Key, Type>				value_type;
		typedef typename Alloc::template
		rebind<value_type>::other						allocType;
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
//		explicit	map(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): _c(comp, allocator) {}
//		explicit	map(const Compare& comp): _c(comp, Alloc()) {}
//		template < class Iter >
//		map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& allocator = Alloc(),
//			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): _c(comp, allocator)
//		{
//			for (; first != last; first++)
//				_c.insert(*first);
//		}
//		map(const Self& other): _c(other._c) {}
//		~map() { clear(); }
		explicit	map(const Compare& comp = Compare(), const Alloc& allocator = Alloc()): Container(comp, allocator) {}
		explicit	map(const Compare& comp): Container(comp, Alloc()) {}
					map(const Self& other): Container(other) {}

		template < class Iter >
		map(Iter first, Iter last, const Compare& comp = Compare(), const Alloc& allocator = Alloc(),
			typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): Container(comp, allocator)
		{
			for (; first != last; first++)
				this->insert(*first);
		}

		~map() { Container::clear(); }


		//_3_Capacity___________________________________________________________________________________________________
//		size_type				size()	const			{ return _c.size(); }
//		size_type				max_size()	const		{ return _c.max_size(); }
//		bool 					empty() const			{ return _c.empty(); }
//		Alloc					get_allocator() const	{ return _c.get_allocator(); }
//
//		//_4_Element_access_____________________________________________________________________________________________
//		iterator				begin()					{ return _c.begin(); }
//		const_iterator			begin()	const			{ return _c.begin(); }
//		iterator				end()					{ return _c.end(); }
//		const_iterator			end() const				{ return _c.end(); }
//		const_reverse_iterator	rend() const			{ return _c.rend(); }
//		reverse_iterator		rend()					{ return _c.rend(); }
//		const_reverse_iterator	rbegin() const			{ return _c.rbegin(); }
//		reverse_iterator		rbegin()				{ return _c.rbegin(); }



//		//_5_Member_functions___________________________________________________________________________________________
//		//__Assignment_operator_____________________
//		Self&	operator=(const Self& other)
//		{
//			this->_c = other._c;
//			return *this;
//		};
//
//		//_6_Modifiers__________________________________________________________________________________________________
//		void							clear()	{ _c.clear(); }
//
//		ft::pair<iterator, bool>		insert(const value_type& X)	{ return (_c.insert(X)); }
//		void							insert(const value_type& X, iterator position) { _c.insert(X); }
//
//		template < class Iter >
//		void	insert(Iter first, Iter last,
//					   typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr)
//		{
//			if (first == last)
//				return ;
//			for (; first != last; ++first)
//				_c.insert(*first);
//		}


	};
}
