#include <smal/Engine/State.hpp>

namespace ma
{
    State::State()
        : m_next {}
    { }

    bool
    State::setNext(const String& next)
    {
        if ( next.equals("") == false )
            m_next = next;

        return false;
    }

    String
    State::next()
    {
        return exch(m_next, {""});
    }

    bool
    State::onAttach(ActorManager& actors)
    {
        return true;
    }

    bool
    State::onDetach()
    {
        return true;
    }

    void
    State::onStart()
    { }

    void
    State::onClean()
    { }

    void
    State::onEnter(ActorManager& actors)
    { }

    void
    State::onLeave()
    { }

    bool
    State::onUpdate()
    {
        return false;
    }

    void
    State::onStep(f32 delta)
    { }

    void
    State::onLast()
    { }
} // namespace ma
