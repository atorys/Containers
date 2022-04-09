//
// vector standard header
// Created by atory on 3/8/22.
//

#pragma once

#include <memory>
#include <iostream>
#include "Iterator/iterator.hpp"
#include "Iterator/iterator_category.hpp"
#include "Iterator/random_access_iterator.hpp"
#include "Iterator/reverse_iterator.hpp"
#include "Iterator/iterator_distance.hpp"
#include "Utils/utility.hpp"

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

		//_1_Member_types_______________________________________________________________________________________________

		typedef vector <Type, Alloc>					Self;
		typedef Alloc									allocator_type;
		typedef typename Alloc::size_type				size_type;
		typedef typename Alloc::difference_type			difference_type;
		typedef typename Alloc::value_type				value_type;

		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef typename Alloc::const_reference			const_reference;

		typedef ft::random_access_iterator < RandIter <Type, difference_type, pointer, reference> >				iterator;
		typedef ft::random_access_iterator < RandIter <Type, difference_type, const_pointer, const_reference> >	const_iterator;
		typedef ft::reverse_iterator < iterator >																reverse_iterator;
		typedef ft::reverse_iterator < const_iterator >															const_reverse_iterator;

		//_2_Constructors_______________________________________________________________________________________________

		explicit	vector(const Alloc& A = Alloc()) : _allocator(A) { Buy(0); }

		explicit	vector(size_type N)
		{
			if (Buy(N))
				_last = Fill(_first, N, Type());
		}

//		vector(size_type N, const Type& X) {
//			if (Buy(N))
//				_last = Fill(_first, N, X);
//		}
		vector(size_type N, const Type& X, const Alloc& A = Alloc()) : _allocator(A)
		{
			if (Buy(N))
				_last = Fill(_first, N, X);
		}
		// copy constructor
		vector(const Self& other)
		{
			if (Buy(other.size()))
				_last = Copy(other.begin(), other.end(), _first);
		}

		template < class Iter >
		vector(Iter first, Iter last, const Alloc& A = Alloc(),
			   typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr): _allocator(A)
		{
			Buy(0);
			insert(this->begin(), first, last);
		}

		template < class Iter >
		vector(Iter first, Iter last, const Alloc& A = Alloc(),
			   typename ft::enable_if<ft::is_integral<Iter>::value>::type* = nullptr): _allocator(A)
		{
			size_type N = (size_type)first;
			if (Buy(N))
				_last = Fill(_first, N, (Type)last);
		}
		~vector() { Clear(); }

		//_3_Capacity___________________________________________________________________________________________________

		size_type				size() const			{ return _first == NULL ? 0 : _last - _first; } // size of active array
		size_type				max_size() const		{ return _allocator.max_size(); } // size of max allocation
		size_type				capacity() const		{ return (_first == NULL ? 0 : _end - _first); } // size of allocated array
		bool					empty() const			{ return (this->size() == 0); }
		Alloc					get_allocator() const	{ return _allocator; }

		//__Reserve___________________________________________________
		// checks that the memory for at least N elements in allocated
		// if not reallocates enough memory
		void					reserve(size_type N)
		{
			if (this->max_size() < N)
				exception_length();
			else if (this->capacity() < N)
			{
				pointer copy = _allocator.allocate(N);
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
				}
				_end = copy + N;
				_last = copy + this->size();
				_first = copy;
			}
		}

		//_4_Element_access_____________________________________________________________________________________________

		iterator					begin()							{ return iterator(_first); }
		const_iterator				begin() const					{ return const_iterator(_first); }
		iterator					end()							{ return iterator(_last); }
		const_iterator				end() const						{ return const_iterator(_last); }
		reverse_iterator			rbegin()						{ return reverse_iterator(this->end()); }
		const_reverse_iterator		rbegin() const					{ return const_reverse_iterator(this->end()); }
		reverse_iterator			rend()							{ return reverse_iterator(this->begin()); }
		const_reverse_iterator		rend() const					{ return const_reverse_iterator(this->begin()); }

		const_reference				operator[](size_type N) const	{ return *(this->begin() + N); } // vector[N]
		reference					operator[](size_type N)			{ return *(this->begin() + N); }
		reference 					front()							{ return *(this->begin()); } // *vector[first]
		const_reference				front() const					{ return *(this->begin()); }
		reference 					back()							{ return *(this->end() - 1); } // *vector[last]
		const_reference				back() const					{ return *(this->end() - 1); }
		pointer 					data()							{ return _first; }
		const_pointer				data() const					{ return _first; }

		reference			at(size_type N) throw(std::out_of_range) // same as vector[N]
		{
			if (this->size() <= N)
				exception_range();
			return *(this->begin() + N);
		}
		const_reference		at(size_type N) const throw(std::out_of_range)// same as vector[N]

		{
			if (this->size() <= N)
				exception_range();
			return *(this->begin() + N);
		}

		//_5_Member_functions___________________________________________________________________________________________
		//__Assignment_operator_____________________
		Self&	operator=(const Self& other)
		{
			if (this == &other)
				;
			else if (other.size() == 0)
				Clear(); // destroy elements
			else if (other.size() <= this->size()) {
				pointer tmp_end = ft::copy(other.begin(), other.end(), _first);
				Destroy(tmp_end, this->_last); // destroy unused cells
				_last = _first + other.size();
			}
			else if (this->capacity() >= other.size()) {
				const_iterator	tmp = other.begin() + this->size();
				ft::copy(other.begin(), tmp, _first);
				_last = Copy(tmp, other.end(), _last);
			}
			else {
				Destroy(_first, _last);
				_allocator.deallocate(_first, _end - _first);
				if (Buy(other.size()))
					_last = Copy(other.begin(), other.end(), this->_first);
			}
			return *this;
		};

		//__Assign__________________________________
		template <class Iter, class Iter2 > // for integral Iter
		void assign(Iter first, Iter2 last, typename ft::enable_if<ft::is_integral<Iter2>::value>::type* = nullptr)
		{
			erase(this->begin(), this->end());
			insert(this->begin(), (size_type)first, (Type)last);
		}

		template <class Iter> // for iterators
		void assign(Iter first, Iter last, typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr)
		{
			erase(this->begin(), this->end());
			insert(this->begin(), first, last);
		}

		//_6_Modifiers__________________________________________________________________________________________________
		//__Insert__________________________________________________________________
		iterator	insert(iterator position, const Type& X) throw(std::length_error)
		{
			size_type offsetIndex = this->size() == 0 ? 0 : position - this->begin();
			this->insert(position, (size_type)1, X);
			return (this->begin() + offsetIndex); // position of inserted element
		}

		// fill : inserts count values before position
		void 	insert(iterator position, size_type count, const Type& X) throw(std::length_error)
		{
			size_type		N = this->capacity();
			pointer			newFirst;
			pointer			newLast;

			if (count == 0) // no element to insert
				return ;
			if (this->max_size() - this->size() < count) // not enough possible allocated memory
				exception_length();
			// if capacity < needed space
			else if (this->size() + count >= this->capacity()) {
				// calculate needed capacity to allocate
				N = std::max(this->size() + count, N * 2);
				newFirst = _allocator.allocate(N); // allocate bigger memory storage
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
			else if ((size_type)(this->end() - position) < count) {
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

//		template < class Iter >
//		void	insert(iterator position, Iter First, Iter Last)
//		{
//			Insert(position, First, Last, ft::Iter_cat(First));
//		}

		template < class Iter > // for integral Iter
		void	insert(iterator position, Iter First, Iter Last, typename ft::enable_if<ft::is_integral<Iter>::value>::type* = nullptr)
		{
			insert(position, (size_type)First, (Type)Last);
		}

		template < class Iter > // for iterators
		void	insert(iterator position, Iter First, Iter Last, typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = nullptr) {
			size_type		count = 0;
			size_type		N = this->capacity();
			pointer			newFirst;
			pointer			newLast;

			ft::distance(First, Last, count); // iter difference -> counter inserted elements
			if (count == 0) // no elements
				return ;
			else if (this->max_size() - this->size() < count) // not enough possible allocated memory
				exception_length();
			else if (this->capacity() < this->size() + count) { // not enough already allocated memory
				N = std::max(this->size() + count, N * 2);
				newFirst = _allocator.allocate(N);

				try {
					newLast = Copy(this->begin(), position, newFirst);
					newLast = Copy(First, Last, newLast);
					Copy(position, this->end(), newLast);
				}
				catch (...) {
					Destroy(newFirst, newLast);
					_allocator.deallocate(newFirst, N);
					throw ;
				}
				if (_first != nullptr) {
					Destroy(_first, _last);
					_allocator.deallocate(_first, _end - _first);
				}
				_end = newFirst + N;
				_last = newFirst + this->size() + count;
				_first = newFirst;
			}
			else if ((size_type)(this->end() - position) < count) { //
				Copy(position, this->end(), position.base() + count);
				Iter Mid = First;
				Mid += this->end() - position;
				try {
					Copy(Mid, Last, _last);
				}
				catch (...) {
					Destroy(position.base() + count, _last + count);
					throw ;
				}
				_last += count;
				ft::copy(First, Mid, position);
			}
			else if (count > 0) {
				iterator	newEnd = this->end();
				_last = Copy(newEnd - count, newEnd, _last);
				ft::copy_backward(position, newEnd - count, newEnd);
				ft::copy(_first, _last, position);
			}
		}

		//__Erase___________________________
		iterator	erase(iterator position)
		{
			ft::copy(position + 1, this->end(), position);
			Destroy(_last - 1, _last);
			--_last;
			return position;
		}
		iterator	erase(iterator First, iterator Last)
		{
			if (First != Last) { // active elements offset from [Last; End()] to First
				pointer	newLast = ft::copy(Last, this->end(), First.base());
				Destroy(newLast, _last); // erasing tail
				_last = newLast;
			}
			return First;
		}

		//__Clear______
		void	clear()
		{
			erase(this->begin(), this->end());
		}

		//__Push_back___________________
		void	push_back(const Type& X)
		{
			insert(this->end(), X);
		}

		//__Pop_back______
		void	pop_back()
		{
			erase(this->end() - 1);
		}

		//__Resize________________
		void	resize(size_type N)
		{
			resize(N, Type());
		}

		void	resize(size_type N, Type X)
		{
			if (this->size() < N)
				insert(this->end(), N - this->size(), X);
			else if (this->size() > N)
				erase(this->begin() + N, this->end());
		}

		//__Swap____________________
		void	swap(Self& other)
		{
			 if (this->_allocator == other._allocator) {
				 std::swap(_first, other._first);
				 std::swap(_last, other._last);
				 std::swap(_end, other._end);
			 }
			 else {
				 Self	tmp = *this;
				 *this = other;
				 other = tmp;
			 }
		}

	protected:
		Alloc		_allocator;
		pointer		_first; // HEAD
		pointer		_last;	// TAIL : position AFTER last active element if _first != 0
		pointer		_end;	// END of allocated memory

		/* uses allocator "Alloc" to allocate N * sizeof(Alloc::value_type)
		 * bytes of uninitialized storage
		 * an array of type Alloc::value_type[N] is created in the storage,
		 * but none of its elements are constructed							*/
		bool	Buy(size_type N)
		{
			_first = nullptr;
			_last = nullptr;
			_end = nullptr;
			if (N == 0)
				return false;
			_first = _allocator.allocate(N); // number of objects, ptr to nearby memory location
			_last = _first; // means np elements constructed yet
			_end = _first + N;
			return true;
		};

		/* calls the destructor of the elements in the array [first, last) */
		void 	Destroy(pointer first, pointer last)
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
		pointer		Fill(pointer current, size_type N, const Type& X)
		{
			pointer begin = current;
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
		pointer		Copy(Iter first, Iter last, pointer current)
		{
			pointer begin = current;
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

		void 	exception_length() const	{ throw std::length_error("vector too long"); };
		void 	exception_range() const		{ throw std::out_of_range("vector subscript"); };
//		void 	exception_range() const { throw std::out_of_range("vector"); };

	};


	template < class Type, class Alloc > inline
	bool	operator==(const vector<Type, Alloc>& X, const vector<Type, Alloc>& Y)
	{
		return (X.size() == Y.size()) && ft::equal(X.begin(), X.end(), Y.begin());
	}

	template < class Type, class Alloc > inline
	bool	operator!=(const vector<Type, Alloc>& X, const vector<Type, Alloc>& Y)
	{
		return !(X == Y);
	}

	template < class Type, class Alloc > inline
	bool	operator<(const vector<Type, Alloc>& X, const vector<Type, Alloc>& Y)
	{
		return (ft::lexicographical_compare(X.begin(), X.end(), Y.begin(), Y.end()));
	}

	template < class Type, class Alloc > inline
	bool	operator>(const vector<Type, Alloc>& X, const vector<Type, Alloc>& Y)
	{
		return (Y < X);
	}

	template < class Type, class Alloc > inline
	bool	operator<=(const vector<Type, Alloc>& X, const vector<Type, Alloc>& Y)
	{
		return !(Y < X);
	}

	template < class Type, class Alloc > inline
	bool	operator>=(const vector<Type, Alloc>& X, const vector<Type, Alloc>& Y)
	{
		return !(X < Y);
	}

	template < class Type, class Alloc > inline
	void	swap(vector<Type, Alloc>& X, vector<Type, Alloc>& Y)
	{
		X.swap(Y);
	}
}
