#include <smal/Memory/ArenaAlloc.hpp>
#include <smal/Memory/helper.hpp>

namespace smal
{
    ArenaAlloc::ArenaAlloc()
        : m_memory {0}
        , m_length {0}
        , m_next {0}
    { }

    ArenaAlloc::ArenaAlloc(void* memory, long length)
        : m_memory {(char*) memory}
        , m_length {length}
        , m_next {m_memory}
    { }

    long
    ArenaAlloc::length() const
    {
        return this->m_length;
    }

    long
    ArenaAlloc::size() const
    {
        long diff =
            this->m_next - this->m_memory;

        return this->m_length - diff;
    }

    bool
    ArenaAlloc::prepare()
    {
        this->m_next =
            this->m_memory;

        return true;
    }

    Part
    ArenaAlloc::reserve(long length)
    {
        Part part = {this, this->m_next, length};

        if ( length < this->size() ) {
            this->m_next += length;

            Memory::set(
                part.memory(),
                part.length(),
                0);

            return part;
        }

        return {};
    }

    bool
    ArenaAlloc::reclaim(const Part& part)
    {
        char* finish = part.memory() +
                       part.length();

        if ( part.origin() != this && part.origin() != 0 )
            return false;

        if ( this->m_next == finish ) {
            if ( part.isNull() == false )
                this->m_next -= part.length();
        } else
            return part.isNull();

        return true;
    }
} // namespace smal
