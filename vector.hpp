//
// vector standard header
// Created by atory on 3/8/22.
//
#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <memory>
#include "Iterator/iterator.hpp"
#include "Iterator/random_access_iterator.hpp"
#include "Iterator/reverse_iterator.hpp"

namespace ft {

	/*
	 * template class VECTOR
	 */
	template < class Type, class Alloc = std::allocator <Type> >
	class	vector {
	public:
		typedef vector <Type, Alloc>					thisType;
		typedef typename Alloc::size_type				sizeType;
		typedef typename Alloc::difference_type			diffType;
		typedef typename Alloc::pointer					ptr;
		typedef typename Alloc::const_pointer			ptrConst;
		typedef typename Alloc::reference				ref;
		typedef typename Alloc::const_reference			refConst;
		typedef typename Alloc::value_type				valueType;

		typedef random_access_iterator < RandIter <Type, diffType, ptr, ref> >				iterator;
		typedef random_access_iterator < RandIter <Type, diffType, ptrConst, refConst> >	iteratorConst;
		typedef reverse_iterator < iterator >												iteratorReverse;
		typedef reverse_iterator < iteratorConst >											iteratorReverseConst;


		vector() : {};
	private:
	};
}

#endif //CONTAINERS_VECTOR_HPP
