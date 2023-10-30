#include <smal/Memory/Origin/StackOrigin.hpp>
#include <smal/Memory/helper.hpp>

namespace ma
{
    StackOrigin::StackOrigin()
        : m_memory {0}
        , m_size {0}
        , m_next {0}
    { }

    StackOrigin::StackOrigin(void* memory, usize size)
        : m_memory {(char*) memory}
        , m_size {size}
        , m_next {m_memory}
    { }

    usize
    StackOrigin::size() const
    {
        return this->m_size;
    }

    usize
    StackOrigin::count() const
    {
        usize diff =
            this->m_next - this->m_memory;

        return this->m_size - diff;
    }

    bool
    StackOrigin::prepare()
    {
        this->m_next =
            this->m_memory;

        return true;
    }

    Page
    StackOrigin::reserve(usize size)
    {
        Page part = {this, this->m_next, size};

        if ( size < this->count() ) {
            this->m_next += size;

            Memory::set(
                part.memory(),
                part.size(),
                0);

            return part;
        }

        return {};
    }

    bool
    StackOrigin::reclaim(Page& part)
    {
        char* finish = part.memory() + part.size();

        if ( part.origin() != this &&
             part.origin() != 0 )
            return false;

        if ( this->m_next == finish ) {
            if ( part.is_null() == false )
                this->m_next -= part.size();

            part = {};
        } else
            return part.is_null();

        return true;
    }

    bool
    StackOrigin::reclaim(Page&& part)
    {
        char* finish = part.memory() + part.size();

        if ( part.origin() != this &&
             part.origin() != 0 )
            return false;

        if ( this->m_next == finish ) {
            if ( part.is_null() == false )
                this->m_next -= part.size();
        } else
            return part.is_null();

        return true;
    }
} // namespace ma
