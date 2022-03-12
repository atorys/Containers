//
// Created by atory on 3/10/22.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

	/**********************************
	 * template class REVERSE_Iterator
	 **********************************/

	template < class RandIter >
	class	reverse_iterator : public ft::iterator <typename iterator_traits<RandIter>::iterCategory,
													typename iterator_traits<RandIter>::valueType,
													typename iterator_traits<RandIter>::diffType,
													typename iterator_traits<RandIter>::pointer,
													typename iterator_traits<RandIter>::reference >
	{
	protected:
		RandIter	_current;

	public:
		typedef	typename iterator_traits<RandIter>::diffType	thisDiff;
		typedef	typename iterator_traits<RandIter>::pointer 	thisPtr;
		typedef	typename iterator_traits<RandIter>::reference	thisRef;
		typedef reverse_iterator<RandIter>						thisType;

		reverse_iterator(){};
		explicit	reverse_iterator(RandIter x) : _current(x) {};
		reverse_iterator(const reverse_iterator<RandIter>& other) : _current(other.base()) {};
		virtual ~reverse_iterator();

		RandIter	base() const { return _current; };

		thisRef		operator*() const
		{
			RandIter tmp = _current;
			return (*(--tmp));
		};

		thisPtr		operator->() const { return &**this; };

		thisType&	operator++() // инкремент декрементирует тк у нас реверсивный указатель
		{
			--_current;
			return *this;
		};

		thisType	operator++(int)
		{
			thisType tmp(this);
			--_current;
			return tmp;
		};

		thisType&	operator--() // декремент инкрементирует тк у нас реверсивный указатель
		{
			++_current;
			return *this;
		};

		thisType	operator--(int)
		{
			thisType tmp = *this;
			++_current;
			return tmp;
		};

		bool	Eq(const thisType& other) const { return (_current == other.base()); };

		thisType&	operator+=(thisDiff N)
		{
			_current -= N;
			return *this;
		};

		thisType	operator+(thisDiff N) const { return (thisType(_current - N)); };

		thisType&	operator-=(thisDiff N)
		{
			_current += N;
			return *this;
		};

		thisType	operator-(thisDiff N) const { return (thisType(_current + N)); };

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
}

#endif //CONTAINERS_REVERSE_ITERATOR_HPP
