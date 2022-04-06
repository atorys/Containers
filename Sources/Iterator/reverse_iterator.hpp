//
// Created by atory on 3/10/22.
//

#pragma once
#include "iterator.hpp"

namespace ft {

	/**********************************
	 * template class REVERSE_Iterator
	 **********************************/

	template < class RandIter >
	class	reverse_iterator : public ft::iterator <typename iterator_traits<RandIter>::iterator_category,
													typename iterator_traits<RandIter>::value_type,
													typename iterator_traits<RandIter>::difference_type,
													typename iterator_traits<RandIter>::pointer,
													typename iterator_traits<RandIter>::reference >
	{
	protected:
		RandIter	_current;

	public:
		typedef	typename RandIter::difference_type	thisDiff;
		typedef	typename RandIter::reference		thisRef;
		typedef	typename RandIter::pointer			thisPtr;
		typedef reverse_iterator<RandIter>			Self;

		reverse_iterator(){};
		explicit	reverse_iterator(RandIter x) : _current(x) {};
		reverse_iterator(const reverse_iterator<RandIter>& other) : _current(other.base()) {};
		virtual ~reverse_iterator() {};

		RandIter	base() const			{ return _current; };
		thisRef		operator*() const		{ RandIter tmp = _current; return (*(--tmp)); };
		thisPtr		operator->() const		{ return &**this; };

		Self&		operator++() // инкремент декрементирует тк у нас реверсивный указатель
		{
			--_current;
			return *this;
		};

		Self	operator++(int)
		{
			Self tmp = *this;
			--_current;
			return tmp;
		};

		Self&	operator--() // декремент инкрементирует тк у нас реверсивный указатель
		{
			++_current;
			return *this;
		};

		Self	operator--(int)
		{
			Self tmp = *this;
			++_current;
			return tmp;
		};

		bool	Eq(const Self& other) const { return (_current == other.base()); };

		Self&	operator+=(thisDiff N)
		{
			_current -= N;
			return *this;
		};

		Self	operator+(thisDiff N) const { return (Self(_current - N)); };

		Self&	operator-=(thisDiff N)
		{
			_current += N;
			return *this;
		};

		Self	operator-(thisDiff N) const { return (Self(_current + N)); };

		thisRef 	operator[](thisDiff N) const { return *(*this + N);	};
	};

	template < class RandIter > inline
	bool	operator==(const reverse_iterator<RandIter>& A, const reverse_iterator<RandIter>& B)
	{
		return A.Eq(B);
	}

	template < class RandIter > inline
	bool	operator!=(const reverse_iterator<RandIter>& A, const reverse_iterator<RandIter>& B)
	{
		return !(A.Eq(B));
	}

	template < class RandIter > inline
	reverse_iterator<RandIter>	operator+(typename iterator_traits<RandIter>::difference_type N,
												  const reverse_iterator<RandIter>& x)
	{
		return (x - N);
	}
}
