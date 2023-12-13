#ifndef SMAL_MEMORY_PAGE_TABLE_HPP
#define SMAL_MEMORY_PAGE_TABLE_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    class PageTable
    {
    public:
        /**
         *
        */
        PageTable();

        /**
         *
         */
        PageTable(void* memory, u32 size, u32 page);

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
        u32
        page() const;

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
        push(void* memory);

        /**
         *
         */
        char*
        pull();

        /**
         *
         */
        char*
        find(u32 index) const;

        /**
         *
         */
        char*
        convert(u32 index, u32 size) const;

    private:
        /**
         *
         */
        static const u32 s_node_size;

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
        u32 m_page;

        /**
         *
         */
        u32 m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_PAGE_TABLE_HPP
