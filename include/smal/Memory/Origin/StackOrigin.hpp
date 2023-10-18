#ifndef SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace smal
{
    class StackOrigin
        : public BaseOrigin
    {
    public:
        /**
         * @brief
         */
        StackOrigin();

        /**
         * @brief
         *
         * @param memory
         * @param length
         */
        StackOrigin(void* memory, usize length);

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
         * @return true
         * @return false
         */
        bool
        prepare();

        /**
         * @brief
         *
         * @param length
         *
         * @return Part
         */
        Part
        reserve(usize length);

        /**
         * @brief
         *
         * @param part
         *
         * @return true
         * @return false
         */
        bool
        reclaim(Part& part);

        /**
         * @brief
         *
         * @param part
         *
         * @return true
         * @return false
         */
        bool
        reclaim(Part&& part);

    private:
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
        char* m_next;
    };
} // namespace smal

#endif // SMAL_MEMORY_ORIGIN_STACK_ORIGIN_HPP
