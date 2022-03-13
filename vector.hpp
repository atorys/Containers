//
// vector standard header
// Created by atory on 3/8/22.
//

#pragma once
#include <memory>
#include "Iterator/iterator.hpp"
#include "Iterator/iterator_category.hpp"
#include "Iterator/random_access_iterator.hpp"
#include "Iterator/reverse_iterator.hpp"

namespace ft {

	/*************************
	 * template class VECTOR
	 *************************/

	template < class Type, class Alloc = std::allocator <Type> >
	class	vector {
	public:
		typedef vector <Type, Alloc>					thisType;
		typedef typename Alloc::size_type				sizeType;
		typedef typename Alloc::difference_type			diffType;
		typedef typename Alloc::value_type				valueType;

		typedef typename Alloc::pointer					ptr;
		typedef typename Alloc::reference				ref;
		typedef typename Alloc::const_pointer			const_ptr;
		typedef typename Alloc::reference				const_ref;

		typedef ft::random_access_iterator < RandIter <Type, diffType, ptr, ref> >				iterator;
		typedef ft::random_access_iterator < RandIter <Type, diffType, const_ptr, const_ref> >	const_iterator;
		typedef ft::reverse_iterator < iterator >												reverse_iterator;
		typedef ft::reverse_iterator < const_iterator >											const_reverse_iterator;


		vector() { Buy(0); };
		explicit	vector(sizeType N)
		{
			if (Buy(N))
				_last = Fill(_first, N, Type());
		};
		explicit	vector(sizeType N, const Type& X)
		{
			if (Buy(N))
				_last = Fill(_first, N, X);
		};
		vector(const thisType& other) // copy constructor
		{
			if (Buy(other.size()))
				_last = Copy(other.begin(), other.end(), _first);
		};
		template < class Iter >
				vector(Iter first, Iter last) { Construct(first, last, ft::Iter_cat(first)); }
		template < class Iter >
		void Construct(Iter first, Iter last, ft::Int_iterator_tag)
				{
					sizeType N = static_cast<sizeType>(first);
					if (Buy(N))
						_last = Fill(_first, N, (Type)last);
				}


	protected:
		ptr		_first;
		ptr		_last;
		ptr		_end;

		/* uses allocator "Alloc" to allocate N * sizeof(Alloc::value_type)
		 * bytes of uninitialized storage
		 * an array of type Alloc::value_type[N] is created in the storage,
		 * but none of its elements are constructed							*/
		bool	Buy(sizeType N)
		{
			_first = nullptr;
			_last = nullptr;
			_end = nullptr;
			if (N == 0)
				return false;
			_first = Alloc::allocate(N, (void *)nullptr); // number of objects, ptr to nearby memory location
			_last = _first;
			_end = _first + N;
			return true;
		};

		/* calls the destructor of the object pointed by given ptr */
		void 	Destroy(ptr first, ptr last)
		{
			for (; first != last; first++)
				Alloc::destroy(first);
		};

		/* destroying pointers and deallocating memory */
		void	Clear()
		{
			if (_first != nullptr) {
				Destroy(_first, _last);
				Alloc::deallocate(_first, _end - _first);
			}
			_first = nullptr;
			_last = nullptr;
			_end = nullptr;
		};

		/* constructs an object of type "Type" in allocated uninitialized storage
		 * pointed by "current" using placement-new */
		ptr		Fill(ptr current, sizeType N, const Type& X)
		{
			ptr begin = current;
			try {
				for (; N > 0; --N, ++current)
					Alloc::construct(current, X);
			}
			catch (...) {
				Destroy(begin, current);
				throw ;
			}
			return current;
		};

		template < class Iter >
		ptr		Copy(Iter first, Iter last, ptr current)
		{
			ptr begin = current;
			try {
				for (; first != last; ++current, ++first)
					Alloc::construct(current, *first);
			}
			catch (...) {
				Destroy(begin, current);
				throw ;
			}
			return current;
		};

	};
}
