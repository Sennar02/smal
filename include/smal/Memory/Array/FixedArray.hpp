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
         * @param length
         */
        FixedArray(BaseOrigin* origin, usize length = 0);

        /**
         *
         *
         * @param memory
         * @param length
         */
        FixedArray(void* memory, usize length);

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
        length() const;

        /**
         *
         *
         * @param length
         *
         * @return True.
         * @return False.
         */
        bool
        resize(usize length);

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
        usize m_length;
    };
} // namespace ma

#include <smal/Memory/impl/FixedArray.tpp>

#endif // SMAL_MEMORY_ARRAY_FIXED_ARRAY_HPP
