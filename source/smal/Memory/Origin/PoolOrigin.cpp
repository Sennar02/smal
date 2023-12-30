#include <smal/Memory/Origin/PoolOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    struct Head
    {
        bool used;
        char fill[7u];
    };

    static const u32 s_node_size =
        sizeof(void*);

    static const u32 s_head_size =
        sizeof(Head);

    PoolOrigin::PoolOrigin()
        : BaseOrigin()
        , m_list {0}
        , m_page {s_node_size}
        , m_count {0}
    { }

    PoolOrigin::PoolOrigin(void* memory, u32 size, u32 page)
        : BaseOrigin(memory, size)
        , m_list {0}
        , m_page {s_node_size}
        , m_count {0}
    {
        prepare(page);
    }

    u32
    PoolOrigin::page() const
    {
        return m_page - s_head_size;
    }

    u32
    PoolOrigin::count() const
    {
        return m_count;
    }

    bool
    PoolOrigin::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_size;
        char* ptr = (char*) memory - s_head_size;

        if ( inf <= ptr && ptr < sup )
            return (ptr - m_memory) % m_page == 0;

        return false;
    }

    bool
    PoolOrigin::availab(u32 size) const
    {
        if ( m_count != 0 )
            return size + s_head_size <= m_page;

        return false;
    }

    bool
    PoolOrigin::prepare(u32 page)
    {
        char* addr  = m_memory + s_head_size;
        u32   count = 0;

        if ( page < s_node_size ) return false;

        if ( m_memory != 0 ) {
            memset(m_memory, 0, m_size);

            m_page = page + s_head_size;
            count  = m_size / m_page;

            for ( u32 i = 0; i < count; i++ )
                insert(addr + m_page * i);
        }

        return m_memory != 0;
    }

    bool
    PoolOrigin::prepare()
    {
        return prepare(m_page);
    }

    char*
    PoolOrigin::acquire(u32 size)
    {
        char* addr = (char*) remove(size);
        Head* head = (Head*) (addr - s_head_size);

        if ( addr != 0 ) {
            size       = m_page - s_head_size;
            head->used = true;

            return (char*)
                memset(addr, 0, size);
        }

        return 0;
    }

    char*
    PoolOrigin::acquire()
    {
        return acquire(m_page - s_head_size);
    }

    bool
    PoolOrigin::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - s_head_size);

        if ( memory != 0 ) {
            if ( contains(memory) == false )
                return false;

            if ( head->used ) {
                head->used = false;
                insert(memory);
            } else
                return false;
        }

        return true;
    }

    void*
    PoolOrigin::remove(u32 size)
    {
        void** node = m_list;
        u32    page = m_page - s_head_size;

        if ( size == 0 ) return 0;

        if ( size <= page && m_count != 0 ) {
            m_list = (void**) *node;
            m_count -= 1u;

            return (void*) node;
        }

        return 0;
    }

    void
    PoolOrigin::insert(void* memory)
    {
        void** node = (void**) memory;

        if ( memory != 0 ) {
            *node  = (void*) m_list;
            m_list = node;

            m_count += 1u;
        }
    }
} // namespace ma
