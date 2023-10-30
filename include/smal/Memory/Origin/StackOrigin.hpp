#ifndef SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class StackOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        StackOrigin();

        /**
         *
         *
         * @param memory
         * @param size
         */
        StackOrigin(void* memory, usize size);

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
         * @return True.
         * @return False.
         */
        bool
        prepare();

        /**
         *
         *
         * @param size
         *
         * @return
         */
        Page
        reserve(usize size);

        /**
         *
         *
         * @param part
         *
         * @return True.
         * @return False.
         */
        bool
        reclaim(Page& part);

        /**
         *
         *
         * @param part
         *
         * @return True.
         * @return False.
         */
        bool
        reclaim(Page&& part);

    private:
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
        char* m_next;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
