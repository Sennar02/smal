#ifndef SMAL_MEMORY_PAGE_HPP
#define SMAL_MEMORY_PAGE_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    class Page
    {
    public:
        /**
         * Creates a null memory page.
         */
        Page();

        /**
         * Creates a memory page.
         *
         * @param origin Origin of memory.
         * @param memory Pointer to page.
         * @param size   Size of the page in bytes.
         */
        Page(BaseOrigin* origin, void* memory, usize size);

        /**
         * Verifies if the page points to null.
         *
         * @return True if it points to null.
         * @return False otherwise.
         */
        bool
        is_null() const;

        /**
         * @return A read-only pointer to the origin of memory.
         */
        const BaseOrigin*
        origin() const;

        /**
         * @return A pointer to the page.
         */
        char*
        memory();

        /**
         * @return A read-only pointer to the page.
         */
        const char*
        memory() const;

        /**
         * @return Size of the page in bytes.
         */
        usize
        size() const;

    private:
        /**
         * Pointer to the origin of memory.
         */
        BaseOrigin* m_origin;

        /**
         * Pointer to page.
         */
        char* m_memory;

        /**
         * Size of the page in bytes.
         */
        usize m_size;
    };
} // namespace ma

#endif // SMAL_MEMORY_PAGE_HPP
