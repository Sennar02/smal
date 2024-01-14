#ifndef SMAL_MEMORY_PAGE_TABLE_HPP
#define SMAL_MEMORY_PAGE_TABLE_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    class PageTable
    {
    public:
        using Item = char*;

        /**
         *
         */
        static const u32 s_size = sizeof(Item);

    public:
        /**
         *
         */
        PageTable();

        /**
         *
         */
        PageTable(void* memory, u32 length);

        /**
         *
         */
        char*
        memory() const;

        /**
         *
         */
        u32
        length() const;

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
        Item* m_memory;

        /**
         *
         */
        u32 m_length;

        /**
         *
         */
        u32 m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_PAGE_TABLE_HPP
