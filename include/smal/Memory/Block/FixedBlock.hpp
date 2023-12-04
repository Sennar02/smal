#ifndef SMAL_MEMORY_BLOCK_FIXED_BLOCK_HPP
#define SMAL_MEMORY_BLOCK_FIXED_BLOCK_HPP

#include <smal/Memory/Block/BaseBlock.hpp>

namespace ma
{
    template <class Type>
    class FixedBlock
        : public BaseBlock<Type>
    {
    public:
        /**
         *
         */
        FixedBlock();

        /**
         *
         */
        FixedBlock(BaseAlloc& alloc, u32 size);

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        bool
        resize(u32 size);

        /**
         *
         */
        Type&
        operator[](u32 index);

        /**
         *
         */
        const Type&
        operator[](u32 index) const;

    private:
        /**
         *
         */
        static const u32 s_type_size =
            sizeof(Type);

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

#include <smal/Memory/Block/impl/FixedBlock.tpp>

#endif // SMAL_MEMORY_BLOCK_FIXED_BLOCK_HPP
