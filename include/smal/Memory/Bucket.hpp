#ifndef SMAL_MEMORY_BUCKET_HPP
#define SMAL_MEMORY_BUCKET_HPP

#include <smal/Memory/Alloc/PoolAlloc.hpp>

namespace ma
{
    template <class Type>
    class Bucket
    {
    public:
        /**
         *
         */
        Bucket();

        /**
         *
         */
        Bucket(void* memory, usize size);

        /**
         *
         */
        Type*
        acquire();

        /**
         *
         */
        bool
        release(Type* addr);

    private:
        /**
         *
         */
        static const usize s_type_size =
            sizeof(Type);

    private:
        /**
         *
         */
        PoolAlloc m_alloc;
    };
} // namespace ma

#include <smal/Memory/impl/Bucket.tpp>

#endif // SMAL_MEMORY_BUCKET_HPP
