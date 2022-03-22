//
// Created by atory on 3/22/22.
//

#pragma once

namespace ft {
	template < class Iter, class Type >
	void	fill(Iter first, Iter last, const Type& X) {
		for (; first != last; ++first)
			*first = X;
	}
}
