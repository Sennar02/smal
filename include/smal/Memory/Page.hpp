#ifndef SMAL_MEMORY_PAGE_HPP
#define SMAL_MEMORY_PAGE_HPP

#include <smal/Memory/define.hpp>

namespace smal
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
         * @param length Length of the page in bytes.
         */
        Page(BaseOrigin* origin, void* memory, usize length);

        /**
         * Verifies if the page points to null.
         *
         * @return True if it points to null.
         * @return False otherwise.
         */
        bool
        isNull() const;

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
         * @return Length of the page in bytes.
         */
        usize
        length() const;

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
         * Length of the page in bytes.
         */
        usize m_length;
    };
} // namespace smal

#endif // SMAL_MEMORY_PAGE_HPP
