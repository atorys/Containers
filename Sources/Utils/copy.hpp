//
// Created by atory on 3/23/22.
//

#pragma once

namespace ft {

	template < class BiDirIter1, class BiDirIter2>
	BiDirIter2	copy(BiDirIter1 start, BiDirIter1 end, BiDirIter2 X)
	{
		for (; start != end; ++X, ++start)
			*X = *start;
		return X;
	}
	template < class BiDirIter1, class BiDirIter2>
	BiDirIter2	copy_backward(BiDirIter1 start, BiDirIter1 end, BiDirIter2 X)
	{
		while (start != end)
			*(--X) = *(--end);
		return X;
	}
}
