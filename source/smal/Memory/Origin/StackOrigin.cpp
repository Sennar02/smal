#include <smal/Memory/Origin/StackOrigin.hpp>
#include <smal/Memory/helper.hpp>

namespace ma
{
    StackOrigin::StackOrigin()
        : m_memory {0}
        , m_length {0}
        , m_next {0}
    { }

    StackOrigin::StackOrigin(void* memory, usize length)
        : m_memory {(char*) memory}
        , m_length {length}
        , m_next {m_memory}
    { }

    usize
    StackOrigin::length() const
    {
        return this->m_length;
    }

    usize
    StackOrigin::size() const
    {
        usize diff =
            this->m_next - this->m_memory;

        return this->m_length - diff;
    }

    bool
    StackOrigin::prepare()
    {
        this->m_next =
            this->m_memory;

        return true;
    }

    Page
    StackOrigin::reserve(usize length)
    {
        Page part = {this, this->m_next, length};

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
    StackOrigin::reclaim(Page& part)
    {
        char* finish = part.memory() + part.length();

        if ( part.origin() != this && part.origin() != 0 )
            return false;

        if ( this->m_next == finish ) {
            if ( part.isNull() == false )
                this->m_next -= part.length();

            part = {};
        } else
            return part.isNull();

        return true;
    }

    bool
    StackOrigin::reclaim(Page&& part)
    {
        char* finish = part.memory() + part.length();

        if ( part.origin() != this && part.origin() != 0 )
            return false;

        if ( this->m_next == finish ) {
            if ( part.isNull() == false )
                this->m_next -= part.length();
        } else
            return part.isNull();

        return true;
    }
} // namespace ma
