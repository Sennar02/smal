#ifndef SMAL_MEMORY_PART_HPP
#define SMAL_MEMORY_PART_HPP

#include <smal/Memory/define.hpp>

namespace smal
{
    class Part
    {
    public:
        /**
         * @brief
         */
        Part();

        /**
         * @brief
         *
         * @param origin
         * @param memory
         * @param length
         */
        Part(BaseOrigin* origin, void* memory, usize length);

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool
        isNull() const;

        /**
         * @brief
         *
         * @return const BaseOrigin&
         */
        const BaseOrigin*
        origin() const;

        /**
         * @brief
         *
         * @return char*
         */
        char*
        memory();

        /**
         * @brief
         *
         * @return const char*
         */
        const char*
        memory() const;

        /**
         * @brief
         *
         * @return usize
         */
        usize
        length() const;

    private:
        /**
         * @brief
         */
        BaseOrigin* m_origin;

        /**
         * @brief
         */
        char* m_memory;

        /**
         * @brief
         */
        usize m_length;
    };
} // namespace smal

#endif // SMAL_MEMORY_PART_HPP
