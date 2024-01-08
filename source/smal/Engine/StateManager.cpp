#include <smal/Engine/StateManager.hpp>

namespace ma
{
    StateManager::StateManager(u32 size)
        : AssetManager(size)
        , m_table {g_origin, size}
        , m_stack {g_origin, size}
    { }

    bool
    StateManager::launch(u32 index)
    {
        State* state = 0;

        state = m_table.find(index, state);

        leave();

        if ( state != 0 )
            m_stack.insert(state);
        else
            m_stack.remove();

        return enter();
    }

    State*
    StateManager::active()
    {
        State* state = 0;
        u32    index = m_stack.count() - 1u;

        if ( m_stack.isEmpty() == false )
            state = m_stack[index];

        return state;
    }

    State*
    StateManager::active() const
    {
        State* state = 0;
        u32    index = m_stack.count() - 1u;

        if ( m_stack.isEmpty() == false )
            state = m_stack[index];

        return state;
    }

    bool
    StateManager::enter()
    {
        State* state = active();

        if ( state != 0 )
            state->onEnter();

        return state != 0;
    }

    bool
    StateManager::leave()
    {
        State* state = active();

        if ( state != 0 )
            state->onLeave();

        return state != 0;
    }
} // namespace ma
