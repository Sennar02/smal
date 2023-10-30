#ifndef SMAL_MEMORY_ARRAY_FIXED_ARRAY_HPP
#define SMAL_MEMORY_ARRAY_FIXED_ARRAY_HPP

#include <smal/Memory/define.hpp>

namespace ma
{
    template <class Type>
    class FixedArray
    {
    public:
        static const usize SIZE = sizeof(Type);

    public:
        /**
         *
         */
        FixedArray();

        /**
         *
         *
         * @param origin
         * @param size
         */
        FixedArray(BaseOrigin* origin, usize size = 0);

        /**
         *
         *
         * @param memory
         * @param size
         */
        FixedArray(void* memory, usize size);

        /**
         *
         */
        virtual ~FixedArray();

        /**
         *
         *
         * @return usize
         */
        usize
        size() const;

        /**
         *
         *
         * @param size
         *
         * @return True.
         * @return False.
         */
        bool
        resize(usize size);

        /**
         *
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](usize index);

        /**
         *
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](usize index) const;

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

#include <smal/Memory/impl/FixedArray.tpp>

#endif // SMAL_MEMORY_ARRAY_FIXED_ARRAY_HPP
