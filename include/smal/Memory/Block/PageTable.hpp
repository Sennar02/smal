#ifndef SMAL_MEMORY_BLOCK_PAGE_TABLE_HPP
#define SMAL_MEMORY_BLOCK_PAGE_TABLE_HPP

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
        PageTable(void* memory, usize size, usize page);

        /**
         *
         */
        usize
        size() const;

        /**
         *
         */
        usize
        count() const;

        /**
         *
         */
        usize
        page() const;

        /**
         *
         */
        bool
        is_empty() const;

        /**
         *
         */
        bool
        is_full() const;

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
        find(usize index) const;

        /**
         *
         */
        char*
        convert(usize index, usize size) const;

    private:
        using Node = char*;

        /**
         *
         */
        static const usize s_node_size =
            sizeof(Node);

    private:
        /**
         *
         */
        Node* m_memory;

        /**
         *
         */
        usize m_size;

        /**
         *
         */
        usize m_page;

        /**
         *
         */
        usize m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_BLOCK_PAGE_TABLE_HPP
