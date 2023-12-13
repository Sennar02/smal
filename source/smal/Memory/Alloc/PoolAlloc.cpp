#include <smal/Memory/Alloc/PoolAlloc.hpp>
#include <smal/Memory/util.hpp>

namespace ma
{
    struct PoolAlloc::Node
    {
        Node* next;
    };

    union PoolAlloc::Head
    {
        struct
        {
            bool used;
        };

        char memory[16];
    };

    const u32 PoolAlloc::s_node_size =
        sizeof(Node);

    const u32 PoolAlloc::s_head_size =
        sizeof(Head);

    PoolAlloc::PoolAlloc()
        : m_memory {0}
        , m_size {0}
        , m_count {0}
        , m_list {0}
        , m_page {s_node_size}
    { }

    PoolAlloc::PoolAlloc(void* memory, u32 size, u32 page)
        : m_memory {(char*) memory}
        , m_size {size}
        , m_count {0}
        , m_list {0}
        , m_page {s_node_size}
    {
        if ( m_memory == 0 ) m_size = 0;

        if ( page >= s_node_size )
            prepare(page);
    }

    u32
    PoolAlloc::page() const
    {
        return m_page;
    }

    u32
    PoolAlloc::count() const
    {
        return m_count;
    }

    u32
    PoolAlloc::size() const
    {
        return m_size;
    }

    u32
    PoolAlloc::next() const
    {
        if ( m_count != 0 )
            return m_page;

        return 0;
    }

    char*
    PoolAlloc::memory() const
    {
        return m_memory;
    }

    bool
    PoolAlloc::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_size;

        return inf <= memory && memory < sup;
    }

    bool
    PoolAlloc::prepare(u32 page)
    {
        Node* node = 0;
        Node* next = 0;
        u32   step = page + s_head_size;

        if ( page < s_node_size ) return false;

        if ( m_memory != 0 ) {
            node = (Node*) ((char*) m_memory + s_head_size);

            m_count = m_size / step;
            m_list  = node;
            m_page  = page;

            memoryWipe(m_memory, m_size);

            for ( u32 i = 1; i < m_count; i++ ) {
                next = (Node*) ((char*) node + step);

                node->next = next;
                node       = next;
            }
        }

        return m_memory != 0;
    }

    bool
    PoolAlloc::prepare()
    {
        return prepare(m_page);
    }

    char*
    PoolAlloc::acquire(u32 size)
    {
        char* addr = (char*) m_list;
        Head* head = (Head*) (addr - s_head_size);

        if ( size == 0 ) return 0;

        if ( size <= m_page && m_count != 0 ) {
            m_count -= 1;

            m_list     = m_list->next;
            head->used = true;

            return memoryWipe(addr, m_page);
        }

        return 0;
    }

    char*
    PoolAlloc::acquire()
    {
        return acquire(m_page);
    }

    bool
    PoolAlloc::release(void* memory)
    {
        char* addr = (char*) memory - s_head_size;
        Head* head = (Head*) addr;
        Node* node = (Node*) memory;

        u32 full = m_page + s_head_size;
        u32 dist = ((char*) head - m_memory) % full;

        if ( memory != 0 ) {
            if ( contains(addr) == false )
                return false;

            if ( dist != 0 || head->used == false )
                return false;

            m_count += 1;

            memoryWipe(head, m_page);

            node->next = m_list;
            m_list     = node;
        }

        return true;
    }
} // namespace ma
