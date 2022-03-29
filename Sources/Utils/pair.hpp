//
// Created by atory on 3/29/22.
//

#pragma once

namespace ft {

	template < class A, class B >
	struct	pair {
		A		_first;
		B		_second;

		pair(): _first(A()), _second(B()) {}

		template < class T1, class T2 >
		pair(const pair<T1, T2>& other): _first(other._first), _second(other._second) {}
		pair(const A& X, const B& Y): _first(X), _second(Y) {}

		pair&	operator=(const pair& other)
		{
			if (this == &other)
				return *this;
			_first = other._first;
			_second = other._second;
			return *this;
		}

		void	swap(const pair& other)
		{
			pair<A, B>	tmp(other);

			other._first = this->_first;
			other._second = this->_second;
			this = tmp;
		}
	};

	template < class T1, class T2 >
	pair<T1, T2>	make_pair(const T1& X, const T2& Y)
	{
		return pair<T1, T2>(X, Y);
	}

	template < class T1, class T2 >
	bool	operator==(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return (X._first == Y._first && X._second == Y._second);
	}

	template < class T1, class T2 >
	bool	operator!=(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return !(X == Y);
	}

	template < class T1, class T2 >
	bool	operator<(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return (X._first < Y._first || (!(Y._first < X._first) && X._second < Y._second));
	}

	template < class T1, class T2 >
	bool	operator>(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return Y < X;
	}

	template < class T1, class T2 >
	bool	operator>=(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return !(X < Y);
	}

	template < class T1, class T2 >
	bool	operator<=(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return !(Y < X);
	}
}