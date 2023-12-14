#include <smal/Memory/Origin/PoolOrigin.hpp>

#include <string.h> // memset

namespace ma
{
    struct Pref
    {
        bool used;
        char fill[15];
    };

    static const u32 s_node_size =
        sizeof(void*);

    static const u32 s_pref_size =
        sizeof(Pref);

    PoolOrigin::PoolOrigin()
        : BaseOrigin()
        , m_list {0}
        , m_page {s_node_size}
        , m_count {0}
    { }

    PoolOrigin::PoolOrigin(const SimpleBuffer<char>& buffer, u32 page)
        : BaseOrigin(buffer)
        , m_list {0}
        , m_page {s_node_size}
        , m_count {0}
    {
        prepare(page);
    }

    PoolOrigin::PoolOrigin(void* memory, u32 size, u32 page)
        : PoolOrigin(SimpleBuffer<char> {memory, size}, page)
    { }

    u32
    PoolOrigin::page() const
    {
        return m_page;
    }

    u32
    PoolOrigin::count() const
    {
        return m_count;
    }

    bool
    PoolOrigin::contains(void* memory) const
    {
        u32 size = m_page + s_pref_size;

        char* inf = m_memory;
        char* sup = m_memory + m_size;
        char* ptr = (char*) memory - s_pref_size;

        if ( inf <= ptr && ptr < sup )
            return (ptr - m_memory) % size == 0;

        return false;
    }

    bool
    PoolOrigin::remains(u32 size) const
    {
        if ( m_count != 0 )
            return size <= m_page;

        return false;
    }

    bool
    PoolOrigin::prepare(u32 page)
    {
        u32    full = page + s_pref_size;
        void** node = 0;

        if ( page < s_node_size ) return false;

        if ( m_memory != 0 ) {
            node = (void**) (m_memory + s_pref_size);

            m_list  = node;
            m_page  = page;
            m_count = m_size / full;

            memset(m_memory, 0, m_size);

            for ( u32 i = 0; i < m_count; i++ ) {
                *node = (void*) ((char*) node + full);
                node  = (void**) *node;
            }
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
        char* addr = (char*) m_list;
        Pref* pref = (Pref*) (addr - s_pref_size);

        if ( size == 0 ) return 0;

        if ( size <= m_page && m_count != 0 ) {
            m_count -= 1;
            m_list = (void**) *m_list;

            pref->used = true;

            return (char*)
                memset(addr, 0, m_page);
        }

        return 0;
    }

    char*
    PoolOrigin::acquire()
    {
        return acquire(m_page);
    }

    bool
    PoolOrigin::release(void* memory)
    {
        char*  addr = (char*) memory;
        Pref*  pref = (Pref*) (addr - s_pref_size);
        void** node = (void**) memory;

        if ( memory != 0 ) {
            if ( contains(memory) == false )
                return false;

            if ( pref->used == false )
                return false;

            m_count += 1;

            memset(pref, 0, m_page);

            *node  = (void*) m_list;
            m_list = node;
        }

        return true;
    }
} // namespace ma
