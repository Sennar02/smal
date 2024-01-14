#ifndef SMAL_MEMORY_LAYOUT_FIXED_LAYOUT_HPP
#define SMAL_MEMORY_LAYOUT_FIXED_LAYOUT_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    class FixedLayout
    {
    public:
        /**
         *
         */
        FixedLayout(void* memory, u32 items, u32 scale);

        /**
         *
         */
        FixedLayout(BaseOrigin& origin, u32 items, u32 scale);

        /**
         *
         */
        char*
        memory() const;

        /**
         *
         */
        u32
        length(u32 scale) const;

        /**
         *
         */
        bool
        resize(u32 items, u32 scale);

        /**
         *
         */
        char&
        find(u32 index, u32 scale) const;

    protected:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_length;
    };
} // namespace ma

#endif // SMAL_MEMORY_LAYOUT_FIXED_LAYOUT_HPP
