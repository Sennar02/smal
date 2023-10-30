#include <smal/Struct/Algo/QuickSort.hpp>

namespace ma
{
    template <typename Type, template <class> class Array, class Func>
    void
    QuickSort::sort(Array<Type>& array, usize count, Func comp)
    {
        QuickSort::sort(array, 0, count - 1, comp);
    }

    template <typename Type, template <class> class Array, class Func>
    void
    QuickSort::sort(Array<Type>& array, usize start, usize stop, Func comp)
    {
        while ( start < stop ) {
            usize pivot = QuickSort::part(array, start, stop, comp);

            if ( pivot - start + 1 < stop - pivot ) {
                QuickSort::sort(array, start, pivot, comp);
                start = pivot + 1;
            } else {
                QuickSort::sort(array, pivot + 1, stop, comp);
                stop = pivot;
            }
        }
    }

    template <typename Type, template <class> class Array, class Func>
    usize
    QuickSort::part(Array<Type>& array, usize start, usize stop, Func comp)
    {
        Type  item = array[start];
        usize lidx = start - 1;
        usize ridx = stop + 1;

        while ( true ) {
            while ( comp(item, array[--ridx]) ) // item < array[]
                ;
            while ( comp(array[++lidx], item) ) // array[] < item
                ;

            if ( lidx < ridx )
                swap(array[lidx], array[ridx]);
            else
                return ridx;
        }
    }
} // namespace ma
