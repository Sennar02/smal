#include <smal/Engine/ActorManager.hpp>

namespace ma
{
    ActorManager::ActorManager(u32 size)
        : m_list {g_origin, size}
        , m_count {0}
        , m_next {g_max_u32, 0}
    { }

    Actor
    ActorManager::acquire()
    {
        Actor actor = recycle();

        if ( actor.m_code == g_max_u32 ) {
            actor.m_code = m_list.count();

            if ( m_list.insert(actor) == false )
                return {};
        }

        return actor;
    }

    bool
    ActorManager::release(const Actor& actor)
    {
        u32 code = actor.m_code;

        if ( code >= m_list.count() )
            return false;

        if ( m_count < m_list.count() ) {
            if ( m_list[code].m_code != code )
                return false;

            swap(m_list[code], m_next);

            m_next.m_vers += 1u;
            m_count += 1u;
        }

        return true;
    }

    Actor
    ActorManager::recycle()
    {
        Actor actor = m_next;
        u32   code  = actor.m_code;

        if ( m_count != 0 ) {
            swap(m_list[code], m_next);
            m_count -= 1u;

            return actor;
        }

        return {};
    }
} // namespace ma
