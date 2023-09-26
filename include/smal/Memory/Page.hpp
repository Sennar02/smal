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
        is_null() const;

        /**
         * @brief
         *
         * @return PageAlloc*
         */
        PageAlloc*
        get_origin() const;

        /**
         * @brief
         *
         * @return char*
         */
        char*
        get_memory() const;

        /**
         * @brief
         *
         * @return char*
         */
        char*
        get_finish() const;

        /**
         * @brief
         *
         * @return long
         */
        long
        get_length() const;

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
