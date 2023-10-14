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
        ArenaAlloc(void* memory, usize length);

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
        reclaim(const Part& part);

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

#endif // SMAL_MEMORY_STACK_ALLOC_HPP
