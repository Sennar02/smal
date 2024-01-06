#include <smal/Engine/StateManager.hpp>

namespace ma
{
    StateManager::StateManager(u32 size)
        : m_table {g_origin, size}
        , m_stack {g_origin, size}
    { }

    bool
    StateManager::attach(u32 code, State& state)
    {
        if ( code == 0 ) return false;

        if ( m_table.insert(code, &state) ) {
            if ( state.onAttach() )
                return true;

            m_table.remove(code);
        }

        return false;
    }

    bool
    StateManager::detach(u32 code)
    {
        State* state = 0;
        bool    result = false;

        state = m_table.find(code, state);

        if ( state != 0 ) {
            result = state->onDetach();

            if ( m_table.remove(code) )
                return result;
        }

        return false;
    }

    bool
    StateManager::launch(u32 code)
    {
        State* state = 0;

        state = m_table.find(code, state);

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
        u32     index  = m_stack.count() - 1u;

        if ( m_stack.isEmpty() == false )
            state = m_stack[index];

        return state;
    }

    State*
    StateManager::active() const
    {
        State* state = 0;
        u32     index  = m_stack.count() - 1u;

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
    }

    bool
    StateManager::leave()
    {
        State* state = active();

        if ( state != 0 )
            state->onLeave();
    }
} // namespace ma
