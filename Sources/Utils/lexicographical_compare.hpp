//
// Created by atory on 3/20/22.
//

#pragma once

namespace ft {

	/**
	 * функция возвращает TRUE, когда последовательность, обозначенная
	 * итераторами в диапазоне [first, last] лексикографически меньше,
	 * чем другая последовательность, иначе FALSE
	 */
	template < class Iter1, class Iter2 >
	bool	lexicographical_compare(Iter1 X, Iter1 lastX, Iter2 Y, Iter2 lastY)
	{
		for (; (X != lastX) && (Y != lastY); ++X, ++Y)
		{
			if (*X < *Y)
				return true;
			if (*Y < *X)
				return false;
		}
		return (X == lastX) && (Y != lastY);
	}

	template < class Iter1, class Iter2, class Compare >
	bool	lexicographical_compare(Iter1 X, Iter1 lastX, Iter2 Y, Iter2 lastY, Compare cmp)
	{
		for (; (X != lastX) && (Y != lastY); ++X, ++Y)
		{
			if (cmp(*X, *Y))
				return true;
			if (cmp(*Y, *X))
				return false;
		}
		return (X == lastX) && (Y != lastY);
	}
}
