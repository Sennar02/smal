#ifndef SMAL_MEMORY_PAGE_HPP
#define SMAL_MEMORY_PAGE_HPP

#include <smal/Memory/define.hpp>

namespace smal
{
    class Page
    {
    public:
        /**
         * @brief
         */
        Page();

        /**
         * @brief
         *
         * @param origin
         * @param memory
         * @param length
         */
        Page(PageAlloc* origin, void* memory, long length);

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
         * @return PageAlloc*
         */
        PageAlloc*
        origin() const;

        /**
         * @brief
         *
         * @return char*
         */
        char*
        memory() const;

        /**
         * @brief
         *
         * @return long
         */
        long
        length() const;

    private:
        /**
         * @brief
         */
        PageAlloc* m_origin;

        /**
         * @brief
         */
        void* m_memory;

        /**
         * @brief
         */
        long m_length;
    };
} // namespace smal

#endif // SMAL_MEMORY_PAGE_HPP
