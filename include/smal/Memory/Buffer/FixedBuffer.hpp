#ifndef SMAL_MEMORY_BUFFER_FIXED_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_FIXED_BUFFER_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    template <class Type>
    class FixedBuffer
    {
    public:
        /**
         *
         */
        FixedBuffer();

        /**
         *
         */
        FixedBuffer(BaseAlloc& alloc, usize size = 0);

        /**
         *
         */
        FixedBuffer(void* memory, usize size);

        /**
         *
         */
        virtual ~FixedBuffer();

        /**
         *
         */
        usize
        size() const;

        /**
         *
         */
        bool
        resize(usize size);

        /**
         *
         */
        void
        clear();

        /**
         *
         */
        Type&
        operator[](usize index);

        /**
         *
         */
        const Type&
        operator[](usize index) const;

    private:
        /**
         *
         */
        static const usize g_type_size =
            sizeof(Type);

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

#include <smal/Memory/Buffer/impl/FixedBuffer.tpp>

#endif // SMAL_MEMORY_BUFFER_FIXED_BUFFER_HPP
