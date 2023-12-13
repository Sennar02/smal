#ifndef SMAL_MEMORY_MEMORY_MODULE_HPP
#define SMAL_MEMORY_MEMORY_MODULE_HPP

#include <smal/Memory/PageTable.hpp>

namespace ma
{
    class MemoryModule
    {
    public:
        /**
         *
         */
        MemoryModule(u32 size, u32 page);

        /**
         *
         */
        ~MemoryModule();

        /**
         *
         */
        template <class Alloc, class... Args>
        bool
        request(Alloc& alloc, Args&&... args);

    private:
        /**
         *
         */
        PageTable m_table;
    };

    template <class Alloc, class... Args>
    bool
    MemoryModule::request(Alloc& alloc, Args&&... args)
    {
        char* addr = 0;
        u32   page = m_table.page();

        if ( m_table.isFull() == false ) {
            addr = (char*) calloc(1, page);

            if ( m_table.push(addr) )
                alloc = {addr, page, forw<Args>(args)...};
        }

        return addr != 0;
    }
} // namespace ma

#endif // SMAL_MEMORY_MEMORY_MODULE_HPP
