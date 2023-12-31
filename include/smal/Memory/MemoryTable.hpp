#ifndef SMAL_MEMORY_MEMORY_TABLE_HPP
#define SMAL_MEMORY_MEMORY_TABLE_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    class MemoryTable
    {
    public:
        /**
         *
         */
        static const u32 s_node_size;

    public:
        /**
         *
         */
        MemoryTable();

        /**
         *
         */
        MemoryTable(void* memory, u32 size);

        /**
         *
         */
        char*
        memory() const;

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        bool
        isEmpty() const;

        /**
         *
         */
        bool
        isFull() const;

        /**
         *
         */
        bool
        insert(void* memory);

        /**
         *
         */
        char*
        remove();

        /**
         *
         */
        char*
        find(u32 index) const;

        /**
         *
         */
        char*
        convert(u32 byte, u32 page) const;

    private:
        /**
         *
         */
        char** m_memory;

        /**
         *
         */
        u32 m_size;

        /**
         *
         */
        u32 m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_MEMORY_TABLE_HPP
