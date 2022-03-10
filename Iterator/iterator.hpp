//
// iterator standard header
// Created by atory on 3/9/22.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

namespace ft {

    /*
     * CATEGORY TAGS
     * пустые типы, используются для выбора алгоритмов
     */
    struct  input_iterator_tag {};
    struct  output_iterator_tag {};
    struct  forward_iterator_tag : public input_iterator_tag {};
    struct  bidirectional_iterator_tag : public forward_iterator_tag {};
    struct  random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct	Int_iterator_tag {};


    /*
     * template class ITERATOR
     */
        template <  class _Cat, class _Type, class _Diff = std::ptrdiff_t, class _Ptr = _Type*, class _Ref = _Type& >
        struct  iterator {
        public:
            typedef _Cat    iterCategory;
            typedef _Type   valueType;
            typedef _Diff   diffType;
            typedef _Ptr    pointer;
            typedef _Ref    reference;
        };

        template < class Type, class Diff, class Ptr, class Ref >
        struct  BiDirIter : public iterator < bidirectional_iterator_tag, Type, Diff, Ptr, Ref > {};

        template < class Type, class Diff, class Ptr, class Ref >
		struct	RandIter : public iterator < random_access_iterator_tag, Type, Diff, Ptr, Ref > {};

		struct	OutIter : public iterator < output_iterator_tag, void, void, void, void > {};



    /*
     *  template class ITERATOR_TRAITS
     *  интерфейс к свойствам типов итераторов
     *  partial specialization
     */
        template < class Iter >
        struct  iterator_traits {
            typedef typename Iter::iterCategory     iterCategory;
            typedef typename Iter::valueType        valueType;
            typedef typename Iter::diffType         diffType;
            typedef typename Iter::pointer          pointer;
            typedef typename Iter::reference        reference;
        };

        template < class Type >
        struct  iterator_traits < Type* > {
            typedef random_access_iterator_tag      iterCategory;
            typedef Type                            valueType;
            typedef ptrdiff_t                       diffType;
            typedef Type*                           pointer;
            typedef Type&                           reference;
        };

        template < class Type >
        struct  iterator_traits < const Type* > {
            typedef random_access_iterator_tag      iterCategory;
            typedef Type                            valueType;
            typedef ptrdiff_t                       diffType;
            typedef const Type*                     pointer;
            typedef const Type&                     reference;
        };
}

#endif //CONTAINERS_ITERATOR_HPP
