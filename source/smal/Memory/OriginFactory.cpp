#include <smal/Memory/OriginFactory.hpp>

namespace ma
{
    OriginFactory::OriginFactory(u32 length)
        : m_table {calloc(1u, length * s_size), length}
    { }

    OriginFactory::~OriginFactory()
    {
        while ( m_table.isEmpty() == false )
            free(m_table.remove());

        free(m_table.memory());
    }
} // namespace ma
