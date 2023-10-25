#ifndef SMAL_MEMORY_DEFINE_HPP
#define SMAL_MEMORY_DEFINE_HPP

#include <smal/Memory/depend.hpp>

namespace ma
{
    class Page;
    class PageTable;

    class BaseOrigin;
    class PoolOrigin;
    class StackOrigin;

    class Creator;

    template <class Type>
    class FixedArray;

    template <class Type>
    class PagedArray;
} // namespace ma

#endif // SMAL_MEMORY_DEFINE_HPP
