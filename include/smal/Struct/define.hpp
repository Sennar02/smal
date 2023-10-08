#ifndef SMAL_STRUCT_DEFINE_HPP
#define SMAL_STRUCT_DEFINE_HPP

#include <smal/Struct/depend.hpp>

namespace smal
{
    template <class Type, class Value>
    class ITable;

    template <class Type, template <class> class Array>
    class Vector;

    template <class Type, template <class> class Array>
    class SparseTable;
} // namespace smal

#endif // SMAL_STRUCT_DEFINE_HPP
