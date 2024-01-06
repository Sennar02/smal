#include <smal/Engine/State.hpp>

namespace ma
{
    State::State()
        : m_next {0}
    { }

    bool
    State::setNext(u32 next)
    {
        m_next = next;

        return false;
    }

    u32
    State::next()
    {
        return exch(m_next, 0u);
    }

    bool
    State::onAttach()
    {
        return true;
    }

    bool
    State::onDetach()
    {
        return true;
    }

    void
    State::onEnter()
    { }

    void
    State::onLeave()
    { }
} // namespace ma
