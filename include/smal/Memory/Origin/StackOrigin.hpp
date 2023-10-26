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
         * @param length
         */
        StackOrigin(void* memory, usize length);

        /**
         *
         *
         * @return
         */
        usize
        length() const;

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
         * @return True.
         * @return False.
         */
        bool
        prepare();

        /**
         *
         *
         * @param length
         *
         * @return
         */
        Page
        reserve(usize length);

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
        usize m_length;

        /**
         *
         */
        char* m_next;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
