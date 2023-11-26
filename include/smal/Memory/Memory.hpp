#ifndef SMAL_MEMORY_MEMORY_SYSTEM_HPP
#define SMAL_MEMORY_MEMORY_SYSTEM_HPP

#include <smal/Memory/Alloc/StackAlloc.hpp>

namespace ma
{
    class Memory
    {
    public:
        /**
         *
         */
        Memory(usize size);

        /**
         *
         */
        ~Memory();

        /**
         *
         */
        template <class Alloc>
        Alloc
        create(usize size);

        /**
         *
         */
        template <class Alloc>
        Alloc
        create(usize size, usize page);

    private:
        /**
         *
         */
        StackAlloc m_alloc;
    };
} // namespace ma

#include <smal/Memory/impl/Memory.tpp>

#endif // SMAL_MEMORY_MEMORY_SYSTEM_HPP
