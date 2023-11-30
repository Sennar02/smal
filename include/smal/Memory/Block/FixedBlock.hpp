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
        FixedBlock(const BaseAlloc& alloc, usize size);

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
        static const usize s_type_size =
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

#include <smal/Memory/Block/impl/FixedBlock.tpp>

#endif // SMAL_MEMORY_BLOCK_FIXED_BLOCK_HPP
