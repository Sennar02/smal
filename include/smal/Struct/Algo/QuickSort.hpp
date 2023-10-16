#ifndef SMAL_STRUCT_QUICK_SORT_HPP
#define SMAL_STRUCT_QUICK_SORT_HPP

namespace smal
{
    class QuickSort
    {
    public:
        /**
         * @brief
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
         * @brief
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
         * @brief
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
} // namespace smal

#include <smal/Struct/impl/QuickSort.tpp>

#endif // SMAL_STRUCT_QUICK_SORT_HPP
