#ifndef SMAL_STRUCT_ALGO_QUICK_SORT_HPP
#define SMAL_STRUCT_ALGO_QUICK_SORT_HPP

namespace ma
{
    class QuickSort
    {
    public:
        /**
         *
         *
         * @tparam Type
         * @tparam Array
         * @tparam Func
         *
         * @param array
         * @param size
         * @param func
         */
        template <class Type, template <class> class Array, class Func>
        static void
        sort(Array<Type>& array, usize size, Func func);

    private:
        /**
         *
         *
         * @tparam Type
         * @tparam Array
         * @tparam Func
         *
         * @param array
         * @param start
         * @param stop
         * @param func
         */
        template <class Type, template <class> class Array, class Func>
        static void
        sort(Array<Type>& array, usize start, usize stop, Func func);

        /**
         *
         *
         * @tparam Type
         * @tparam Array
         * @tparam Func
         *
         * @param array
         * @param start
         * @param stop
         * @param func
         *
         * @return usize
         */
        template <class Type, template <class> class Array, class Func>
        static usize
        part(Array<Type>& array, usize start, usize stop, Func func);
    };
} // namespace ma

#include <smal/Struct/impl/QuickSort.tpp>

#endif // SMAL_STRUCT_ALGO_QUICK_SORT_HPP
