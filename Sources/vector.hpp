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
#include "Utils/fill.hpp"

namespace ft {

	/**
	 * template class VECTOR
	 * Sequence container representing dynamic array
	 *
	 * May allocate some extra storage to accommodate for possible growth
	 * Elements are accessed by their position in the sequence
	 *
	 * ! If a reallocation happens, all iterators/pointers/references
	 * pointing to position and beyond are invalid !
	 */

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
		 *********************************************************/
//		vector() { Buy(0); }
		explicit	vector(const Alloc& A = Alloc()) : _allocator(A) { Buy(0); }

		explicit	vector(sizeType N)
		{
			if (Buy(N))
				_last = Fill(_first, N, Type());
		}

		vector(sizeType N, const Type& X) {
			if (Buy(N))
				_last = Fill(_first, N, X);
		}
		vector(sizeType N, const Type& X, const Alloc& A = Alloc()) : _allocator(A)
		{
			if (Buy(N))
				_last = Fill(_first, N, X);
		}
		// copy constructor
		vector(const thisType& other)
		{
			if (Buy(other.size()))
				_last = Copy(other.cbegin(), other.cend(), _first);
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
		 **********************************************************************************************/
		sizeType				size() const			{ return _first == NULL ? 0 : _last - _first; } // size of active array
		sizeType				max_size() const		{ return _allocator.max_size(); } // size of max allocation
		sizeType				capacity() const		{ return (_first == NULL ? 0 : _end - _first); } // size of allocated array
		bool					empty() const			{ return (this->size() == 0); }
		Alloc					get_allocator() const	{ return _allocator; }

		iterator				begin()					{ return iterator(_first); }
		const_iterator			cbegin() const			{ return const_iterator(_first); }
		iterator				end()					{ return iterator(_last); }
		const_iterator			cend() const			{ return const_iterator(_last); }
		reverse_iterator		rbegin()				{ return reverse_iterator(this->end()); }
		const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(this->end()); }
		reverse_iterator		rend()					{ return reverse_iterator(this->begin()); }
		const_reverse_iterator	rend() const			{ return const_reverse_iterator(this->begin()); }

		const_ref				operator[](sizeType N) const	{ return *(this->begin() + N); }
		ref						operator[](sizeType N)			{ return *(this->begin() + N); }
		ref 					front()							{ return *(this->begin()); }
		const_ref				front() const					{ return *(this->begin()); }
		ref 					back()							{ return *(this->end() - 1); }
		const_ref				back() const					{ return *(this->end() - 1); }

		ref			at(sizeType N) throw(std::out_of_range)
		{
			if (this->size() <= N)
				exception_range();
			return *(this->begin() + N);
		}
		const_ref	at(sizeType N) const throw(std::out_of_range)
		{
			if (this->size() <= N)
				exception_range();
			return *(this->begin() + N);
		}

		/** Overloads
		 *********************************************************/
		thisType&	operator=(const thisType& other)
		{
			if (this == &other)
				;
			else if (other.size() == 0)
				Clear();
			else if (other.size() <= this->size()) {
				ptr tmp_end = std::copy(other.cbegin(), other.cend(), _first);
				Destroy(tmp_end, this->_last);
				_last = _first + other.size();
			}
			else {
				Destroy(_first, _last);
				_allocator.deallocate(_first, _end - _first);
				if (Buy(other.size()))
					_last = Copy(other.cbegin(), other.cend(), this->_first);
			}
			return *this;
		};

		/** Insert
		*******************/
		// single element
		iterator	insert(iterator position, const Type& X) throw(std::length_error)
		{
			sizeType offsetIndex = this->size() == 0 ? 0 : position - this->begin();
			this->insert(position, (sizeType)1, X);
			return (this->begin() + offsetIndex);
		}

		// fill : inserts count values before position
		void 	insert(iterator position, sizeType count, const Type& X) throw(std::length_error)
		{
			sizeType	N = this->capacity();
			ptr			newFirst;
			ptr			newLast;

			if (count == 0)
				return ;
			if (this->max_size() - this->size() < count)
				exception_length();
			// if capacity < needed space
			else if (this->size() + count >= this->capacity()) {
				// calculate needed capacity to allocate
				N = (this->max_size() - N/2 < N) ? 0 : N + N/2;
				if (this->size() + count >= N)
					N = this->size() + count;

				newFirst = _allocator.allocate(N, (void *)nullptr); // allocate bigger memory storage
				try {
					newLast = Copy(this->begin(), position, newFirst); // copy elements before position in new storage
					newLast = Fill(newLast, count, X); // fill memory with new elements in range [position; position + count]
					Copy(position, this->end(), newLast); // copy tail after position + count
				}
				catch (...) {
					Destroy(newFirst, newLast);
					_allocator.deallocate(newFirst, N);
					throw ;
				}
				if (_first != nullptr) { // free unused memory
					Destroy(_first, _last);
					_allocator.deallocate(_first, _end - _first);
				}
				_last = newFirst + this->size() + count;
				_end = newFirst + N; // new_first + new_capacity();
				_first = newFirst;
			}
			//
			else if (this->end() - position < count) {
				// смещаем элементы с [position; end] на [position + count; end]
				// чтобы вставить новые и не потерять старые значения
				Copy(position, this->end(), position.base() + count);
				//
				try {
					Fill(_last, count - (this->end() - position), X);
				}
				catch (...) {
					Destroy(position.base() + count, _last + count);
					throw ;
				}
				_last += count;
				ft::fill(position, this->end() - count, X);
			}
			else { // if current capacity is enough
				iterator	newEnd = this->end();

				_last = Copy(newEnd - count, newEnd, _last);
				std::copy_backward(position, newEnd - count, newEnd);
				ft::fill(position, position + count, X);
			}
		}

		template < class Iter >
		void	insert(iterator position, Iter First, Iter Last)
		{
			Insert(position, First, Last, ft::Iter_cat(First));
		}

		template < class Iter >
		void	Insert(iterator position, Iter First, Iter Last, ft::Int_iterator_tag) {
			insert(position, (sizeType)First, (Type)Last);
		}
		template < class Iter >
		void	Insert(iterator position, Iter First, Iter Last, ft::input_iterator_tag) {
			for (; First != Last; ++First, ++position)
				position = insert(position, *First);
		}
		template < class Iter >
		void	Insert(iterator position, Iter First, Iter Last, ft::forward_iterator_tag) {
			// (. . .)
		}

		/** Erase
		 *******************/
		iterator	erase(iterator position)
		{
			 // todo: копирование без конструктора !!!
			std::copy(position + 1, this->end(), position);
			Destroy(_last - 1, _last);
			--_last;
			return position;
		}
		iterator	erase(iterator First, iterator Last)
		{
			if (First != Last) { // active elements offset from [Last; End()] to First
				ptr	newLast = std::copy(Last, this->end(), First.base());
				Destroy(newLast, _last); // erasing tail
				_last = newLast;
			}
			return First;
		}

		/** Clear
		 *******************/
		void	clear()
		{
			erase(this->begin(), this->end());
		}
		/** Push_back
		 *******************/
		void	push_back(const Type& X)
		{
			insert(this->end(), X);
		}
		/** Pop_back
		 *******************/
		void	pop_back()
		{
			erase(this->end() - 1);
		}

		void 	reserve(sizeType N)
		{
			if (this->max_size() < N)
				exception_length();
			if (this->capacity() < N)
			{
				ptr copy = _allocator.allocate(N, (void *)nullptr);
				try {
					Copy(this->begin(), this->end(), copy);
				}
				catch (...) {
					_allocator.deallocate(copy, N);
					throw ;
				}
				if (_first != 0)
				{
					Destroy(_first, _last);
					_allocator.deallocate(_first, _end - _first);
					_end = copy + N;
					_last = copy + this->size();
					_first = copy;
				}
			}
		}

		void	resize(sizeType N)
		{
			resize(N, Type());
		}

		void	resize(sizeType N, Type X)
		{
			if (this->size() < N)
				insert(this->end(), N - this->size(), X);
			else if (N < this->size())
				erase(this->begin() + N, this->end());
		}

		template <class Iter>
		void assign(Iter first, Iter last) { Assign(first, last, ft::Iter_cat(first)); }

		template <class Iter>
		void Assign(Iter first, Iter last, ft::Int_iterator_tag)
		{
			erase(this->begin(), this->end());
			insert(this->begin(), first, last);
		}

		void assign(sizeType N, const Type& X)
		{
			Type Y = X;
			erase(this->begin(), this->end());
			insert(this->begin(), N, Y);
		}

	protected:
		Alloc	_allocator;
		ptr		_first; // HEAD
		ptr		_last;	// TAIL : position AFTER last active element if _first != 0
		ptr		_end;	// END of allocated memory

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
			_last = _first; // means np elements constructed yet
			_end = _first + N;
			return true;
		};

		/* calls the destructor of the elements in the array [first, last) */
		void 	Destroy(ptr first, ptr last)
		{
			for (; first != last; first++)
				_allocator.destroy(first);
		};

		/* destroying whole array from the storage, pointers and deallocating memory */
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
