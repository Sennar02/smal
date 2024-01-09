#include <smal/Engine/StateManager.hpp>

namespace ma
{
    StateManager::StateManager(u32 size)
        : m_table {g_origin, size}
        , m_stack {g_origin, size}
    { }

    bool
    StateManager::attach(const String& name, State& state)
    {
        if ( name.equals("") ) return false;

        if ( state.onAttach() )
            return m_table.insert(name, &state);

        return false;
    }

    bool
    StateManager::detach(const String& name)
    {
        State* state  = 0;
        bool   result = false;

        state = m_table.find(name, state);

        if ( state != 0 ) {
            result = state->onDetach();

            if ( m_table.remove(name) )
                return result;
        }

        return false;
    }

    State*
    StateManager::launch(const String& name)
    {
        State* state = active();

        if ( state != 0 ) state->onLeave();

        if ( change(name) ) {
            state = active();

            if ( state != 0 )
                state->onEnter();

            return state;
        }

        return 0;
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
    StateManager::change(const String& name)
    {
        State* state = 0;

        state = m_table.find(name, state);

        if ( state != 0 )
            return m_stack.insert(state);

        return m_stack.remove();
    }
} // namespace ma
