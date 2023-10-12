#ifndef SMAL_MEMORY_STACK_ALLOC_HPP
#define SMAL_MEMORY_STACK_ALLOC_HPP

#include <smal/Memory/Part.hpp>

namespace smal
{
    class ArenaAlloc
    {
    public:
        /**
         * @brief
         */
        ArenaAlloc();

        /**
         * @brief
         *
         * @param memory
         * @param length
         */
        ArenaAlloc(void* memory, long length);

        /**
         * @brief
         *
         * @return long
         */
        long
        length() const;

        /**
         * @brief
         *
         * @return long
         */
        long
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
        reserve(long length);

        /**
         * @brief
         *
         * @param part
         *
         * @return true
         * @return false
         */
        bool
        reclaim(const Part& part);

    private:
        /**
         * @brief
         */
        char* m_memory;

        /**
         * @brief
         */
        long m_length;

        /**
         * @brief
         */
        char* m_next;
    };
} // namespace smal

#endif // SMAL_MEMORY_STACK_ALLOC_HPP
