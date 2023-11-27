#ifndef SMAL_MEMORY_BUCKET_HPP
#define SMAL_MEMORY_BUCKET_HPP

#include <smal/Memory/Handle.hpp>

namespace ma
{
    template <class Type>
    class Bucket
        : private PoolAlloc
    {
    public:
        /**
         *
         */
        Bucket(void* memory, usize size);

        /**
         *
         */
        Handle<Type>
        acquire();

        /**
         *
         */
        bool
        release(Handle<Type>& handle);

    private:
        /**
         *
         */
        static const usize s_type_size =
            sizeof(Type);
    };
} // namespace ma

#include <smal/Memory/impl/Bucket.tpp>

#endif // SMAL_MEMORY_BUCKET_HPP
