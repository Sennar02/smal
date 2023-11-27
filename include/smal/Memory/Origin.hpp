#ifndef SMAL_MEMORY_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    class Origin
    {
    public:
        /**
         *
         */
        Origin(usize size);

        /**
         *
         */
        ~Origin();

        /**
         *
         */
        usize
        size() const;

        /**
         *
         */
        char*
        memory();

        /**
         *
         */
        const char*
        memory() const;

    private:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        usize m_size;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_HPP
