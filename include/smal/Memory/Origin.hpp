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
        Origin(u32 size);

        /**
         *
         */
        ~Origin();

        /**
         *
         */
        u32
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
        u32 m_size;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_HPP
