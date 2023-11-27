#ifndef SMAL_MEMORY_HANDLE_HPP
#define SMAL_MEMORY_HANDLE_HPP

#include <smal/Memory/Alloc/PageAlloc.hpp>

namespace ma
{
    template <class Type>
    class Handle
    {
    public:
        /**
         *
         */
        ~Handle();

        /**
         *
         */
        bool
        is_null() const;

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

        /**
         *
         */
        Type&
        item();

        /**
         *
         */
        const Type&
        item() const;

    private:
        friend Bucket<Type>;

        /**
         *
         */
        Handle(Bucket<Type>* bucket, char* memory);

    private:
        /**
         *
         */
        Bucket<Type>* m_bucket;

        /**
         *
         */
        char* m_memory;
    };
} // namespace ma

#include <smal/Memory/impl/Handle.tpp>

#endif // SMAL_MEMORY_HANDLE_HPP
