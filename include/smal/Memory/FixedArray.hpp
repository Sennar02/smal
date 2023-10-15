#ifndef SMAL_MEMORY_ARRAY_HPP
#define SMAL_MEMORY_ARRAY_HPP

namespace smal
{
    template <class Type>
    class FixedArray
    {
    public:
        static const usize SIZE = sizeof(Type);

    public:
        /**
         * @brief
         */
        FixedArray();

        /**
         * @brief
         *
         * @param origin
         * @param length
         */
        FixedArray(PoolOrigin& origin, usize length = 0);

        /**
         * @brief
         *
         * @param memory
         * @param length
         */
        FixedArray(void* memory, usize length);

        /**
         * @brief
         */
        virtual ~FixedArray();

        /**
         * @brief
         *
         * @return usize
         */
        usize
        length() const;

        /**
         * @brief
         *
         * @param length
         *
         * @return true
         * @return false
         */
        bool
        resize(usize length);

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](usize index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](usize index) const;

    private:
        /**
         * @brief
         */
        char* m_memory;

        /**
         * @brief
         */
        usize m_length;
    };
} // namespace smal

#include <smal/Memory/impl/FixedArray.tpp>

#endif // SMAL_MEMORY_ARRAY_HPP
