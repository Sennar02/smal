#ifndef SMAL_MEMORY_ORIGIN_BASE_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_BASE_ORIGIN_HPP

#include <smal/Memory/Page.hpp>

namespace ma
{
    class BaseOrigin
    {
    public:
        /**
         *
         */
        virtual ~BaseOrigin() = default;

        /**
         *
         *
         * @return True.
         * @return False.
         */
        virtual bool
        prepare() = 0;

        /**
         *
         *
         * @param length
         *
         * @return
         */
        virtual Page
        reserve(usize length) = 0;

        /**
         *
         *
         * @param part
         *
         * @return True.
         * @return False.
         */
        virtual bool
        reclaim(Page& part) = 0;

        /**
         *
         *
         * @param part
         *
         * @return True.
         * @return False.
         */
        virtual bool
        reclaim(Page&& part) = 0;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_BASE_ORIGIN_HPP
