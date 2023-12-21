#ifndef SMAL_MEMORY_ORIGIN_SPLIT_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_SPLIT_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class SplitOrigin
        : public BaseOrigin
    {
    public:
        SplitOrigin();

        SplitOrigin(const FixedBuffer<char>& buffer, u32 unit);

        SplitOrigin(void* memory, u32 size, u32 unit);

        virtual u32
        unit() const;

        virtual bool
        availab(u32 size) const;

        virtual bool
        prepare(u32 unit);

        virtual bool
        prepare();

        virtual char*
        acquire(u32 size);

        virtual bool
        release(void* memory);

    private:
        void*
        search(u32 size) const;

        void*
        split(u32 size) const;

        void
        merge() const;

    private:
        u32 m_unit;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_SPLIT_ORIGIN_HPP
