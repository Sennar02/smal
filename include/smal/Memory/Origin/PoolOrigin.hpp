#ifndef SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP
#define SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP

#include <smal/Memory/Origin/BaseOrigin.hpp>

namespace ma
{
    class PoolOrigin
        : public BaseOrigin
    {
    public:
        PoolOrigin();

        PoolOrigin(const SimpleBuffer<char>& buffer, u32 page);

        PoolOrigin(void* memory, u32 size, u32 page);

        virtual u32
        page() const;

        virtual u32
        count() const;

        virtual bool
        contains(void* memory) const;

        virtual bool
        remains(u32 size) const;

        virtual bool
        prepare(u32 page);

        virtual bool
        prepare();

        virtual char*
        acquire(u32 size);

        virtual char*
        acquire();

        virtual bool
        release(void* memory);

    private:
        void** m_list;

        u32 m_page;

        u32 m_count;
    };
} // namespace ma

#endif // SMAL_MEMORY_ORIGIN_POOL_ORIGIN_HPP
