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
		pair(pair<T1, T2> const& other): first(other.first), second(other.second) {}
		pair(const A& X, const B& Y): first(X), second(Y) {}

		pair&	operator=(pair const& other)
		{
			if (this == &other)
				return *this;
			first = other.first;
			second = other.second;
			return *this;
		}

		void	swap(pair const& other)
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
	bool	operator==(pair<T1, T2> const& X, pair<T1, T2> const& Y)
	{
		return (X.first == Y.first && X.second == Y.second);
	}

	template < class T1, class T2 >
	bool	operator!=(pair<T1, T2> const& X, pair<T1, T2> const& Y)
	{
		return !(X == Y);
	}

	template < class T1, class T2 >
	bool	operator<(pair<T1, T2> const& X, pair<T1, T2> const& Y)
	{
		return (X.first < Y.first || (!(Y.first < X.first) && X.second < Y.second));
	}

	template < class T1, class T2 >
	bool	operator>(pair<T1, T2> const& X, pair<T1, T2> const& Y)
	{
		return Y < X;
	}

	template < class T1, class T2 >
	bool	operator>=(pair<T1, T2> const& X, pair<T1, T2> const& Y)
	{
		return !(X < Y);
	}

	template < class T1, class T2 >
	bool	operator<=(pair<T1, T2> const& X, pair<T1, T2> const& Y)
	{
		return !(Y < X);
	}
}