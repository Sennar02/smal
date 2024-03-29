#ifndef SMAL_MEMORY_UTIL_HPP
#define SMAL_MEMORY_UTIL_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    /**
     *
     */
    template <class Type>
    Type*
    acquire(BaseOrigin& origin, u32 count = 1u);

    /**
     *
    */
    template <class Type>
    bool
    release(BaseOrigin& origin, Type* memory);
} // namespace ma

#include <smal/Memory/inline/util.inl>

#endif // SMAL_MEMORY_UTIL_HPP
