//
// Created by atory on 3/29/22.
//

#pragma once

namespace ft {

	template < class A, class B >
	struct	pair {
		A		first;
		B		second;

		pair(): first(A()), second(B()) {}

		template < class T1, class T2 >
		pair(const pair<T1, T2>& other): first(other.first), second(other.second) {}
		pair(const A& X, const B& Y): first(X), second(Y) {}

		pair&	operator=(const pair& other)
		{
			if (this == &other)
				return *this;
			first = other.first;
			second = other.second;
			return *this;
		}

		void	swap(const pair& other)
		{
			ft::pair<A, B>	tmp(other);

			other.first = this->first;
			other.second = this->second;
			this = tmp;
		}
	};

	template < class T1, class T2 >
	ft::pair<T1, T2>	 make_pair(T1 X, T2 Y)
	{
		return ft::pair<T1, T2>(X, Y);
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