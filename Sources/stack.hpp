//
// Created by atory on 3/24/22.
//

#pragma once

#include <memory>
#include "vector.hpp"

namespace ft {

	/**
	 * template class STACK based on VECTOR
	 * Container adaptor with the functionality of a stack
	 *
	 * The stack pops and pushes the element from the back of the container,
	 * known as a top of a stack
	 */
	template < class Type, class Container = ft::vector <Type> >
	class	stack {
	protected:
		Container	_c;
	public:

		//_1_Member_types_______________________________________________________________________________________________

		typedef typename Container::valueType		valueType;
		typedef typename Container::sizeType		sizeType;

		//_2_Constructors_______________________________________________________________________________________________

		stack(): _c() {};
		explicit	stack(const Container& Cont):	_c(Cont)		{}
		stack(const stack<Type, Container>& other):	_c(other._c)	{}
		~stack() { _c.clear(); }

		//_3_Capacity___________________________________________________________________________________________________

		bool				empty() const	{ return _c.empty(); }
		sizeType			size() const	{ return _c.size(); }

		//_4_Element_access_____________________________________________________________________________________________

		valueType&			top()			{ return _c.back(); }
		const valueType&	top() const		{ return _c.back(); }

		//_5_Modifiers__________________________________________________________________________________________________

		void				push(const valueType& X)						{ _c.push_back(X); }
		void				pop()											{ _c.pop_back(); }
		bool 				eq(const stack<Type, Container>& other) const	{ return (_c == other._c); }
		bool 				less(const stack<Type, Container>& other) const	{ return (_c < other._c); }
	};

	template < class Type, class C > inline
	bool	operator==(const stack<Type, C>& X, const stack<Type, C>& Y)
	{
		return (X.eq(Y));
	}

	template < class Type, class C > inline
	bool	operator!=(const stack<Type, C>& X, const stack<Type, C>& Y)
	{
		return !(X==Y);
	}

	template < class Type, class C > inline
	bool	operator<(const stack<Type, C>& X, const stack<Type, C>& Y)
	{
		return (X.less(Y));
	}

	template < class Type, class C > inline
	bool	operator>(const stack<Type, C>& X, const stack<Type, C>& Y)
	{
		return Y < X;
	}

	template < class Type, class C > inline
	bool	operator<=(const stack<Type, C>& X, const stack<Type, C>& Y)
	{
		return !(Y < X);
	}

	template < class Type, class C > inline
	bool	operator>=(const stack<Type, C>& X, const stack<Type, C>& Y)
	{
		return !(X < Y);
	}
}
