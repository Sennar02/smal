#ifndef SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class PoolOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        PoolOrigin();

        /**
         *
         *
         * @param memory
         * @param size
         * @param page
         */
        PoolOrigin(void* memory, usize size, usize page = 0);

        /**
         *
         *
         * @return
         */
        usize
        size() const;

        /**
         *
         *
         * @return
         */
        usize
        count() const;

        /**
         *
         *
         * @return
         */
        usize
        page() const;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        bool
        prepare();

        /**
         *
         *
         * @param page
         *
         * @return True.
         * @return False.
         */
        bool
        prepare(usize page);

        /**
         *
         *
         * @param size
         *
         * @return
         */
        Page
        reserve(usize size = 0);

        /**
         *
         *
         * @param page
         *
         * @return True.
         * @return False.
         */
        bool
        reclaim(Page& page);

        /**
         *
         *
         * @param page
         *
         * @return True.
         * @return False.
         */
        bool
        reclaim(Page&& page);

    private:
        struct Node
        {
            Node* next;
        };

        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        usize m_size;

        /**
         *
         */
        Node* m_list;

        /**
         *
         */
        usize m_count;

        /**
         *
         */
        usize m_page;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP
