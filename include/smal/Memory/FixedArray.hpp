#ifndef SMAL_MEMORY_ARRAY_HPP
#define SMAL_MEMORY_ARRAY_HPP

namespace smal
{
    template <class Type>
    class FixedArray
    {
    public:
        static const long SIZE = sizeof(Type);

    public:
        /**
         * @brief
         *
         * @param memory
         * @param length
         */
        FixedArray(void* memory, long length);

        /**
         * @brief
         */
        virtual ~FixedArray();

        /**
         * @brief
         *
         * @return long
         */
        long
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
        resize(long length);

        /**
         * @brief
         *
         * @param index
         *
         * @return Type&
         */
        Type&
        operator[](long index);

        /**
         * @brief
         *
         * @param index
         *
         * @return const Type&
         */
        const Type&
        operator[](long index) const;

    private:
        /**
         * @brief
         */
        Type* m_memory;

        /**
         * @brief
         */
        long m_length;
    };
} // namespace smal

#include <smal/Memory/impl/FixedArray.tpp>

#endif // SMAL_MEMORY_ARRAY_HPP
