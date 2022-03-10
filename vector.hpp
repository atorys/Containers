//
// vector standard header
// Created by atory on 3/8/22.
//
#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <memory>
#include "Iterator/iterator.hpp"

namespace ft {

	/*
	 * template class VECTOR VAL
	 */
	template < class Type, class Alloc >
	class	vectorVal {
	protected:
//		vectorVal(Alloc A = Alloc()) : _AVal(A) {};
//		typedef typename A::templaterebind<Type>::other Alty;
//		Alty	_AVal;
	};

	/*
	 * template class VECTOR
	 */
	template < class Type, class Alloc = allocator<Type> >
	class	vector : public vectorVal < Type, Alloc > {
	public:
		typedef vector<Type, Alloc>				thisType;
		typedef vectorVal<Type, Alloc>			thisBase;
		typedef typename Alloc::size_type		sizeType;
		typedef typename Alloc::difference_type	differType;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	pointerConst;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	referenceConst;
		typedef typename Alloc::value_type		valueType;

	private:
	};
}

#endif //CONTAINERS_VECTOR_HPP
