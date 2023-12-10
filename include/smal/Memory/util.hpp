#ifndef SMAL_MEMORY_HELPER_HPP
#define SMAL_MEMORY_HELPER_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    /**
     *
     */
    char*
    memorySet(void* memory, u32 size, char byte);

    /**
     *
     */
    template <class Type, class Alloc>
    Type*
    acquire(Alloc& alloc);

    /**
     *
     */
    template <class Type, class Alloc, class... Args>
    Type*
    acquire(Alloc& alloc, Args&&... args);

    /**
     *
     */
    template <class Type, class Alloc>
    bool
    release(Alloc& alloc, Type* addr);
} // namespace ma

#include <smal/Memory/impl/util.tpp>

#endif // SMAL_MEMORY_HELPER_HPP
