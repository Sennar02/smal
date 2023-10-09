#ifndef SMAL_MEMORY_BUFFER_HPP
#define SMAL_MEMORY_BUFFER_HPP

namespace smal
{
    template <long Len>
    class Buffer
    {
    public:
        inline static const long length = Len;

    public:
        template <class Type>
        Buffer(const Type& memory);

        template <class Type>
        Buffer(Type&& memory);

        template <class Type = char>
        Type*
        memory();

        template <class Type = char>
        const Type*
        memory() const;

    private:
        char m_memory[Len];
    };
} // namespace smal

#include <smal/Memory/impl/Buffer.tpp>

#endif // SMAL_MEMORY_BUFFER_HPP
