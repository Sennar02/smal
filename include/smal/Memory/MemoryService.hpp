#ifndef SMAL_MEMORY_MEMORY_SERVICE_HPP
#define SMAL_MEMORY_MEMORY_SERVICE_HPP

#include <smal/Memory/Alloc/PoolAlloc.hpp>
#include <smal/Memory/Alloc/StackAlloc.hpp>

namespace ma
{
    class MemoryService
    {
    public:
        /**
         *
         */
        MemoryService(u32 size);

        /**
         *
         */
        ~MemoryService();

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        char*
        memory();

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        template <class Alloc, class... Args>
        Alloc
        create(u32 size, Args&&... args);

    private:
        /**
         *
         */
        StackAlloc m_stack;
    };
} // namespace ma

#include <smal/Memory/impl/MemoryService.tpp>

#endif // SMAL_MEMORY_MEMORY_SERVICE_HPP