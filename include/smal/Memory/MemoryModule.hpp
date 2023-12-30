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
        MemoryModule(u32 size);

        /**
         *
         */
        ~MemoryModule();

        /**
         *
         */
        template <class Origin, class... Args>
        Origin
        request(u32 size, Args&&... args);

    private:
        /**
         *
         */
        MemoryTable m_table;
    };

    static MemoryModule g_memory = {256u};
} // namespace ma

#include <smal/Memory/inline/MemoryModule.inl>

#endif // SMAL_MEMORY_MEMORY_MODULE_HPP
