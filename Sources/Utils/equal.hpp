//
// Created by atory on 3/24/22.
//

#pragma once

namespace ft {

	template < class Iter1, class Iter2 >
	bool	equal(Iter1 X, Iter1 lastX, Iter2 Y)
	{
		for (; X != lastX; ++X, ++Y)
			if (!(*X == *Y))
				return false ;
		return true ;
	}

	template < class Iter1, class Iter2, class Compare >
	bool	equal(Iter1 X, Iter1 lastX, Iter2 Y, Compare comp)
	{
		for (; X != lastX; ++X, ++Y)
			if (!comp(*X, *Y))
				return false ;
		return true ;
	}
}
