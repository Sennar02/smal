#include <smal/Engine/Actor.hpp>

namespace ma
{
    Actor::Actor(u32 code, u32 vers)
        : m_code {code}
        , m_vers {vers}
    { }

    Actor::Actor()
        : Actor(g_max_u32, g_max_u32)
    { }

    u32
    Actor::identif() const
    {
        return m_code;
    }

    u32
    Actor::version() const
    {
        return m_vers;
    }

} // namespace ma
