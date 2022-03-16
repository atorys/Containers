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
		typedef typename Alloc::const_reference			const_ref;

		typedef ft::random_access_iterator < RandIter <Type, diffType, ptr, ref> >				iterator;
		typedef ft::random_access_iterator < RandIter <Type, diffType, const_ptr, const_ref> >	const_iterator;
		typedef ft::reverse_iterator < iterator >												reverse_iterator;
		typedef ft::reverse_iterator < const_iterator >											const_reverse_iterator;


		/**	Constructors
		 * **********************************************/

		vector() { Buy(0); } // 1) empty
		explicit	vector(const Alloc& A = Alloc()) : _allocator(A) { Buy(0); } // 2) allocator

		explicit	vector(sizeType N) // 3) elem count
		{
			if (Buy(N))
				_last = Fill(_first, N, Type());
		}

		vector(sizeType N, const Type& X) { // 4) count, object sample
			if (Buy(N))
				_last = Fill(_first, N, X);
		}
		vector(sizeType N, const Type& X, const Alloc& A = Alloc()) : _allocator(A) // 5) count, object sample, allocator
		{
			if (Buy(N))
				_last = Fill(_first, N, X);
		}
		vector(const thisType& other) // 6) copy constructor
		{
			if (Buy(other.size()))
				_last = Copy(other.begin(), other.end(), _first);
		}

		template < class Iter >
		vector(Iter first, Iter last) { Construct(first, last, ft::Iter_cat(first)); }

		template < class Iter >
		void	Construct(Iter first, Iter last, ft::Int_iterator_tag)
				{
					sizeType N = (sizeType)first;
					if (Buy(N))
						_last = Fill(_first, N, (Type)last);
				}
		template < class Iter >
		void	Construct(Iter first, Iter last, ft::input_iterator_tag)
				{
					Buy(0);
					insert(this->begin(), first, last);
				}
		~vector() { Clear(); }

		/**	Methods
		 **********************************************************/
		sizeType	size() const { return _first == 0 ? 0 : _last - _first; }
		sizeType 	max_size() const { return _allocator.max_size(); }
		sizeType 	capacity() const { return (_first == 0 ? 0 : _end - _first); }
		bool		empty() const { return (this->size() == 0); }
		Alloc		get_allocator() const { return _allocator; }

		iterator				begin() { return iterator(_first); }
		const_iterator			begin() const { return const_iterator(_first); }
		iterator				end() { return iterator(_last); }
		const_iterator			end() const { return const_iterator(_last); }
		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator		rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }

		ref			at(sizeType N)
		{
			if (this->size() <= N)
				exception_range();
			return *(this->begin() + N);
		}
		const_ref	at(sizeType N) const
		{
			if (this->size() <= N)
				exception_range();
			return *(this->begin() + N);
		}
		const_ref 	operator[](sizeType N) const { return *(this->begin() + N); }
		ref			operator[](sizeType N) { return *(this->begin() + N); }
		ref 		front() { return *(this->begin()); }
		const_ref	front() const { return *(this->begin()); }
		ref 		back() { return *(this->end() - 1); }
		const_ref	back() const { return *(this->end() - 1); }

		/** Overloads
		 *********************************************************/
		thisType&	operator=(const thisType& other)
		{
			if (this == &other)
				;
			else if (other.size() == 0)
				Clear();
			else if (other.size() <= this->size()) {
				ptr tmp_end = Copy(other.begin(), other.end(), this->_first);
				Destroy(tmp_end, this->_last);
				_last = _first + other.size();
			}
			else {
				Destroy(_first, _last);
				_allocator.deallocate(_first, _end - _first);
				if (Buy(other.size()))
					_last = Copy(other.begin(), other.end(), this->_first);
			}
			return *this;
		};


	protected:
		Alloc	_allocator;
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
			_first = _allocator.allocate(N, (void *)nullptr); // number of objects, ptr to nearby memory location
			_last = _first;
			_end = _first + N;
			return true;
		};

		/* calls the destructor of the object pointed by given ptr */
		void 	Destroy(ptr first, ptr last)
		{
			for (; first != last; first++)
				_allocator.destroy(first);
		};

		/* destroying pointers and deallocating memory */
		void	Clear()
		{
			if (_first != nullptr) {
				Destroy(_first, _last);
				_allocator.deallocate(_first, _end - _first);
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
					_allocator.construct(current, X);
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
					_allocator.construct(current, *first);
			}
			catch (...) {
				Destroy(begin, current);
				throw ;
			}
			return current;
		};

		void 	exception_length() const { throw std::length_error("vector<Type> too long"); };
		void 	exception_range() const { throw std::out_of_range("vector<Type> subscript"); };

	};
}
