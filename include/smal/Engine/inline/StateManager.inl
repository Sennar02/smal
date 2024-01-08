#include <smal/Engine/StateManager.hpp>

namespace ma
{
    struct StateTag
    {
        template <class Type>
        static u32
        get()
        {
            static const u32 tag =
                ++s_count;

            return tag;
        }

        static inline u32 s_count = 0;
    };

    template <class Type>
    bool
    StateManager::attach(Type& state)
    {
        u32 index = StateTag::get<Type>();

        if ( index == 0 ) return false;

        if ( m_table.insert(index, (State*) &state) ) {
            if ( state.onAttach(*this) )
                return true;

            m_table.remove(index);
        }

        return false;
    }

    template <class Type>
    bool
    StateManager::detach()
    {
        u32    index  = StateTag::get<Type>();
        State* state  = 0;
        bool   result = false;

        state = m_table.find(index, state);

        if ( state != 0 ) {
            result = state->onDetach();

            if ( m_table.remove(index) )
                return result;
        }

        return false;
    }
} // namespace ma
