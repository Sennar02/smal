#ifndef SMAL_MEMORY_BASE_ORIGIN_HPP
#define SMAL_MEMORY_BASE_ORIGIN_HPP

#include <smal/Memory/Part.hpp>

namespace smal
{
    class BaseOrigin
    {
    public:
        /**
         * @brief
         */
        virtual ~BaseOrigin() = default;

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        virtual bool
        prepare() = 0;

        /**
         * @brief
         *
         * @param length
         *
         * @return Part
         */
        virtual Part
        reserve(usize length) = 0;

        /**
         * @brief
         *
         * @param part
         *
         * @return true
         * @return false
         */
        virtual bool
        reclaim(Part& part) = 0;

        /**
         * @brief
         *
         * @param part
         * 
         * @return true
         * @return false
         */
        virtual bool
        reclaim(Part&& part) = 0;
    };
} // namespace smal

#endif // SMAL_MEMORY_BASE_ORIGIN_HPP
