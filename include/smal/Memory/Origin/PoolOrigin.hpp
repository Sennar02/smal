#ifndef SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace smal
{
    class PoolOrigin
        : public BaseOrigin
    {
    public:
        /**
         * @brief
         */
        PoolOrigin();

        /**
         * @brief
         *
         * @param memory
         * @param length
         * @param page
         */
        PoolOrigin(void* memory, usize length, usize page = 0);

        /**
         * @brief
         *
         * @return usize
         */
        usize
        length() const;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        size() const;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        page() const;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        prepare();

        /**
         * @brief
         *
         * @param page
         *
         * @return true
         * @return false
         */
        bool
        prepare(usize page);

        /**
         * @brief
         *
         * @param length
         *
         * @return Part
         */
        Part
        reserve(usize length = 0);

        /**
         * @brief
         *
         * @param page
         *
         * @return true
         * @return false
         */
        bool
        reclaim(Part& page);

        /**
         * @brief
         *
         * @param page
         *
         * @return true
         * @return false
         */
        bool
        reclaim(Part&& page);

    private:
        struct Node
        {
            Node* next;
        };

        /**
         * @brief
         */
        char* m_memory;

        /**
         * @brief
         */
        usize m_length;

        /**
         * @brief
         */
        Node* m_list;

        /**
         * @brief
         */
        usize m_size;

        /**
         * @brief
         */
        usize m_page;
    };
} // namespace smal

#endif // SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP
