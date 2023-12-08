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
    template <class Value, class Alloc>
    Value*
    acquire(Alloc& alloc);

    /**
     *
     */
    template <class Value, class Alloc, class... Args>
    Value*
    acquire(Alloc& alloc, Args&&... args);

    /**
     *
     */
    template <class Value, class Alloc>
    bool
    release(Alloc& alloc, Value* value);
} // namespace ma

#include <smal/Memory/impl/util.tpp>

#endif // SMAL_MEMORY_HELPER_HPP
