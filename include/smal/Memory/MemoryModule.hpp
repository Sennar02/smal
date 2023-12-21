#ifndef SMAL_MEMORY_MEMORY_MODULE_HPP
#define SMAL_MEMORY_MEMORY_MODULE_HPP

#include <smal/Memory/MemoryTable.hpp>

namespace ma
{
    class MemoryModule
    {
    public:
        /**
         *
         */
        MemoryModule(u32 size = 2048u);

        /**
         *
         */
        ~MemoryModule();

        /**
         *
         */
        template <class Origin, class... Args>
        bool
        request(Origin& origin, u32 size, Args&&... args);

    private:
        /**
         *
         */
        MemoryTable m_table;
    };
} // namespace ma

#include <smal/Memory/impl/MemoryModule.tpp>

#endif // SMAL_MEMORY_MEMORY_MODULE_HPP
